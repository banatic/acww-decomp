/* Nintendo Wi-Fi Connection offline; see wifi.h and docs/multi-console.md.
 *
 * The network: the access point is also the router, the DHCP server and the name server
 * (192.168.11.1); the console gets 192.168.11.2. Every name resolves, in the order first
 * asked, to 10.0.0.1, 10.0.0.2, ...; what answers there is chosen by the port and, for HTTP,
 * by the Host header: the connection test (conntest.nintendowifi.net, HTTP 200), the account
 * server (nas.nintendowifi.net/ac, fixed answers) and GameSpy's presence server (port 29900).
 * A packet's answer leaves one millisecond (of the bus clock) after the packet; TCP's initial
 * sequence numbers count up from a fixed one. Nothing depends on the host's clock or network.
 *
 * What the library sends and expects was read from its code in the ROM (overlay 65: NitroWiFi's
 * WCM and CPS, NitroDWC's AC, netcheck and auth); the protocols are the public ones (ARP, IPv4,
 * UDP, TCP, DHCP, DNS, HTTP/1.0).
 */
#include "wifi.h"

#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "memory.h"

#define CYCLES_PER_MS 33514u
#define LATENCY CYCLES_PER_MS
#define AP_CHANNEL 1
#define NAS_CHALLENGE "ACWWCHAL" /* the account server's challenge: GameSpy's password */
#define AP_SSID "acww-offline"   /* not 8 bytes long (FreeSpot) nor 32 (a Nintendo spot) */

static const uint8_t AP_MAC[6] = {0x02, 0x00, 0x41, 0x43, 0x57, 0x01};
static const uint8_t LLC[6] = {0xaa, 0xaa, 0x03, 0x00, 0x00, 0x00};

#define NET_ROUTER 0xc0a80b01u /* 192.168.11.1 */
#define NET_CLIENT 0xc0a80b02u /* 192.168.11.2 */
#define NET_MASK 0xffffff00u
#define NET_SERVERS 0x0a000000u /* 10.0.0.x: the names' addresses */

#define ETHER_ARP 0x0806
#define ETHER_IP 0x0800
#define PROTO_ICMP 1
#define PROTO_TCP 6
#define PROTO_UDP 17

enum { MODE_ON = 1, MODE_NO_AP, MODE_NO_DNS, MODE_CONNTEST, MODE_NAS };

/* ---- byte order ---- */

static void be16(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t) (v >> 8);
    p[1] = (uint8_t) v;
}

static void be32(uint8_t *p, uint32_t v)
{
    be16(p, v >> 16);
    be16(p + 2, v);
}

static uint32_t get_be16(const uint8_t *p)
{
    return (uint32_t) p[0] << 8 | p[1];
}

static uint32_t get_be32(const uint8_t *p)
{
    return get_be16(p) << 16 | get_be16(p + 2);
}

static void le16(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t) v;
    p[1] = (uint8_t) (v >> 8);
}

/* ---- the state ---- */

#define FRAMES 256
#define NAMES 16
#define CONNECTIONS 8
#define TCP_IN 8192
#define TCP_OUT 16384
#define TCP_MSS 1024

typedef struct Frame {
    uint64_t at;
    uint16_t length;
    uint8_t data[WIFI_FRAME_MAX];
} Frame;

enum { TCP_FREE, TCP_SYN_RECEIVED, TCP_OPEN, TCP_CLOSED };
enum { SERVICE_HTTP, SERVICE_GPCM, SERVICE_NONE };

typedef struct Tcp {
    int state, service;
    uint32_t server_ip;
    uint16_t client_port, server_port;
    uint32_t rcv_nxt, iss, snd_una; /* snd_una: the bytes of out the client acknowledged + 1 */
    uint32_t window, mss;
    uint8_t in[TCP_IN];
    uint32_t in_length;
    uint8_t out[TCP_OUT];
    uint32_t out_length, out_sent; /* out_sent: the bytes of out that went out */
    int closing, fin_sent, peer_fin;
    int greeted;
} Tcp;

static struct {
    int mode;
    int trace;
    int associated;
    uint8_t client_mac[6];
    Frame *frames; /* a ring, in time order */
    int head, count;
    uint64_t last_at;
    uint16_t ip_id;
    char names[NAMES][64];
    int name_count;
    Tcp tcp[CONNECTIONS];
    uint32_t connections;
    uint64_t sent, received, dropped, http, nas;
    uint64_t ssl_calls;
    char lastname[32]; /* the GameSpy profile's, as the console set it */
} wifi;

#define TRACE(...)                                                                                                            \
    do {                                                                                                                      \
        if (wifi.trace) {                                                                                                     \
            fprintf(stderr, "wifi: frame %u: ", io_frame());                                                                  \
            fprintf(stderr, __VA_ARGS__);                                                                                     \
            fprintf(stderr, "\n");                                                                                            \
        }                                                                                                                     \
    } while (0)

/* ---- the firmware's connection settings ---- */

static uint32_t crc16(const uint8_t *p, uint32_t n)
{
    uint32_t crc = 0;
    for (uint32_t i = 0; i < n; i++) {
        crc ^= p[i];
        for (int k = 0; k < 8; k++) {
            crc = crc & 1 ? (crc >> 1) ^ 0xa001u : crc >> 1;
        }
    }
    return crc & 0xffff;
}

/* The three connection settings (0x100 bytes each, 0x400 before the user settings): the first
 * the access point's SSID with everything automatic (DHCP: the addresses 0xc0-0xd0 zero),
 * status 0 (0xe7) and configured (0xef bit 0); the other two not set (status 0xff). Each ends
 * in its CRC-16 (0xa001, initial value 0) over 0-0xfd. The user ID (0xf0) is left 0: the
 * library creates one with the account server. */
static void firmware_settings(uint8_t *nvram)
{
    uint32_t user = ((uint32_t) nvram[0x20] | (uint32_t) nvram[0x21] << 8) * 8;
    if (user < 0x400) {
        return;
    }
    for (int page = 0; page < 4; page++) {
        uint8_t *p = nvram + user - 0x400 + 0x100 * page;
        memset(p, 0, 0x100);
        if (page == 0) {
            memcpy(p + 0x40, AP_SSID, strlen(AP_SSID));
            p[0xef] = 1;
        } else {
            p[0xe7] = 0xff;
        }
        uint32_t crc = crc16(p, 0xfe);
        p[0xfe] = (uint8_t) crc;
        p[0xff] = (uint8_t) (crc >> 8);
    }
}

int wifi_init(uint8_t *nvram)
{
    memset(&wifi, 0, sizeof(wifi));
    const char *text = getenv("RUN_WIFI");
    if (text == NULL || *text == 0 || strcmp(text, "0") == 0) {
        return 0;
    }
    static const struct {
        const char *name;
        int mode;
    } modes[] = {{"1", MODE_ON}, {"noap", MODE_NO_AP}, {"nodns", MODE_NO_DNS}, {"conntest", MODE_CONNTEST}, {"nas", MODE_NAS}};
    for (size_t i = 0; i < sizeof(modes) / sizeof(modes[0]); i++) {
        if (strcmp(text, modes[i].name) == 0) {
            wifi.mode = modes[i].mode;
        }
    }
    if (wifi.mode == 0) {
        fprintf(stderr, "wifi: RUN_WIFI is 1, noap, nodns, conntest or nas; off\n");
        return 0;
    }
    wifi.trace = getenv("RUN_TRACE") != NULL && strstr(getenv("RUN_TRACE"), "wifi") != NULL;
    static Frame frames[FRAMES];
    wifi.frames = frames;
    firmware_settings(nvram);
    return 1;
}

int wifi_on(void)
{
    return wifi.mode != 0;
}

/* ---- the access point ---- */

int wifi_is_ap(const uint8_t mac[6])
{
    return wifi.mode != 0 && memcmp(mac, AP_MAC, 6) == 0;
}

/* WMBssDesc: its length in halfwords 0, the RSSI 2, the BSSID 4, the SSID's length 0xa and the
 * SSID 0xc, the capabilities 0x2c (ESS, no privacy), the basic and supported rates 0x2e and
 * 0x30 (1 and 2 Mbps), the beacon period 0x32, the DTIM period 0x34, the channel 0x36; no game
 * info (0x3c) and no other elements. */
int wifi_scan(uint32_t channels, const uint8_t bssid[6], const uint8_t *ssid, uint32_t ssid_length, uint32_t match,
              uint8_t desc[WIFI_BSS_SIZE])
{
    static const uint8_t any[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    uint32_t length = (uint32_t) strlen(AP_SSID);
    if (wifi.mode == 0 || wifi.mode == MODE_NO_AP || !(channels & (1u << (AP_CHANNEL - 1)))) {
        return 0;
    }
    if (memcmp(bssid, any, 6) != 0 && memcmp(bssid, AP_MAC, 6) != 0) {
        return 0;
    }
    if (ssid_length != 0 &&
        (match > length || memcmp(ssid, AP_SSID, match) != 0 || (match == ssid_length && ssid_length != length))) {
        return 0;
    }
    memset(desc, 0, WIFI_BSS_SIZE);
    le16(desc, WIFI_BSS_SIZE / 2);
    le16(desc + 2, 0xd0);
    memcpy(desc + 4, AP_MAC, 6);
    le16(desc + 0xa, length);
    memcpy(desc + 0xc, AP_SSID, length);
    le16(desc + 0x2c, 0x0001);
    le16(desc + 0x2e, 0x0003);
    le16(desc + 0x30, 0x0003);
    le16(desc + 0x32, 100);
    le16(desc + 0x34, 1);
    le16(desc + 0x36, AP_CHANNEL);
    return 1;
}

static void tcp_reset_all(void)
{
    memset(wifi.tcp, 0, sizeof(wifi.tcp));
}

void wifi_connect(uint64_t now)
{
    (void) now;
    wifi.associated = 1;
    wifi.head = wifi.count = 0;
    tcp_reset_all();
    TRACE("associated with the access point");
}

void wifi_disconnect(void)
{
    wifi.associated = 0;
    wifi.head = wifi.count = 0;
    tcp_reset_all();
    TRACE("disassociated");
}

/* ---- frames to the console ---- */

static void frame_out(uint64_t at, uint32_t ethertype, const uint8_t *payload, uint32_t length)
{
    if (wifi.count == FRAMES || 8 + length > WIFI_FRAME_MAX) {
        wifi.dropped++;
        return;
    }
    if (at < wifi.last_at) {
        at = wifi.last_at;
    }
    wifi.last_at = at;
    Frame *f = &wifi.frames[(wifi.head + wifi.count) % FRAMES];
    f->at = at;
    memcpy(f->data, LLC, 6);
    be16(f->data + 6, ethertype);
    memcpy(f->data + 8, payload, length);
    f->length = (uint16_t) (8 + length);
    wifi.count++;
}

uint32_t wifi_receive(uint64_t now, uint8_t src[6], uint8_t dst[6], uint8_t *frame, uint32_t room)
{
    if (wifi.count == 0 || wifi.frames[wifi.head].at > now) {
        return 0;
    }
    Frame *f = &wifi.frames[wifi.head];
    wifi.head = (wifi.head + 1) % FRAMES;
    wifi.count--;
    if (f->length > room) {
        wifi.dropped++;
        return 0;
    }
    memcpy(src, AP_MAC, 6);
    memcpy(dst, wifi.client_mac, 6);
    memcpy(frame, f->data, f->length);
    wifi.received++;
    return f->length;
}

/* ---- IP ---- */

static uint32_t checksum_add(uint32_t sum, const uint8_t *p, uint32_t n)
{
    for (uint32_t i = 0; i + 1 < n; i += 2) {
        sum += get_be16(p + i);
    }
    if (n & 1) {
        sum += (uint32_t) p[n - 1] << 8;
    }
    return sum;
}

static uint32_t checksum_end(uint32_t sum)
{
    while (sum >> 16) {
        sum = (sum & 0xffff) + (sum >> 16);
    }
    return ~sum & 0xffff;
}

static void ip_out(uint64_t at, uint32_t proto, uint32_t src, uint32_t dst, const uint8_t *payload, uint32_t length)
{
    static uint8_t p[WIFI_FRAME_MAX];
    if (20 + length + 8 > sizeof(p)) {
        wifi.dropped++;
        return;
    }
    memset(p, 0, 20);
    p[0] = 0x45;
    be16(p + 2, 20 + length);
    be16(p + 4, wifi.ip_id++);
    p[8] = 64;
    p[9] = (uint8_t) proto;
    be32(p + 12, src);
    be32(p + 16, dst);
    be16(p + 10, checksum_end(checksum_add(0, p, 20)));
    memcpy(p + 20, payload, length);
    frame_out(at, ETHER_IP, p, 20 + length);
}

static uint32_t pseudo_sum(uint32_t src, uint32_t dst, uint32_t proto, uint32_t length)
{
    uint8_t h[12];
    be32(h, src);
    be32(h + 4, dst);
    h[8] = 0;
    h[9] = (uint8_t) proto;
    be16(h + 10, length);
    return checksum_add(0, h, 12);
}

static void udp_out(uint64_t at, uint32_t src, uint32_t sport, uint32_t dst, uint32_t dport, const uint8_t *data,
                    uint32_t length)
{
    static uint8_t u[WIFI_FRAME_MAX];
    if (8 + length > sizeof(u) - 40) {
        wifi.dropped++;
        return;
    }
    be16(u, sport);
    be16(u + 2, dport);
    be16(u + 4, 8 + length);
    be16(u + 6, 0);
    memcpy(u + 8, data, length);
    uint32_t sum = checksum_end(checksum_add(pseudo_sum(src, dst, PROTO_UDP, 8 + length), u, 8 + length));
    be16(u + 6, sum ? sum : 0xffff);
    ip_out(at, PROTO_UDP, src, dst, u, 8 + length);
}

/* ---- ARP ---- */

static void arp_in(uint64_t at, const uint8_t *p, uint32_t length)
{
    if (length < 28 || get_be16(p + 6) != 1) {
        return;
    }
    uint32_t target = get_be32(p + 24);
    if (target == get_be32(p + 14)) {
        return; /* the console asking for its own address: nobody else has it */
    }
    uint8_t a[28];
    be16(a, 1);
    be16(a + 2, ETHER_IP);
    a[4] = 6;
    a[5] = 4;
    be16(a + 6, 2);
    memcpy(a + 8, AP_MAC, 6); /* everything off the console is behind the access point */
    be32(a + 14, target);
    memcpy(a + 18, p + 8, 6);
    memcpy(a + 24, p + 14, 4);
    frame_out(at, ETHER_ARP, a, sizeof(a));
}

/* ---- DHCP ---- */

static void dhcp_in(uint64_t at, const uint8_t *p, uint32_t length)
{
    if (length < 240 || p[0] != 1 || get_be32(p + 236) != 0x63825363u) {
        return;
    }
    uint32_t type = 0;
    for (uint32_t i = 240; i < length && p[i] != 0xff;) {
        if (p[i] == 0) {
            i++;
            continue;
        }
        if (i + 1 >= length || i + 2 + p[i + 1] > length) {
            break;
        }
        if (p[i] == 53 && p[i + 1] >= 1) {
            type = p[i + 2];
        }
        i += 2u + p[i + 1];
    }
    uint32_t answer = type == 1 ? 2 : type == 3 ? 5 : 0; /* DISCOVER: OFFER; REQUEST: ACK */
    TRACE("DHCP %u -> %u", type, answer);
    if (answer == 0) {
        return;
    }
    uint8_t r[300];
    memset(r, 0, sizeof(r));
    r[0] = 2;
    r[1] = 1;
    r[2] = 6;
    memcpy(r + 4, p + 4, 4); /* xid */
    memcpy(r + 10, p + 10, 2);
    be32(r + 16, NET_CLIENT);
    be32(r + 20, NET_ROUTER);
    memcpy(r + 28, p + 28, 16);
    be32(r + 236, 0x63825363u);
    uint8_t *o = r + 240;
    *o++ = 53, *o++ = 1, *o++ = (uint8_t) answer;
    *o++ = 54, *o++ = 4, be32(o, NET_ROUTER), o += 4;
    *o++ = 51, *o++ = 4, be32(o, 86400), o += 4;
    *o++ = 1, *o++ = 4, be32(o, NET_MASK), o += 4;
    *o++ = 3, *o++ = 4, be32(o, NET_ROUTER), o += 4;
    *o++ = 6, *o++ = 4, be32(o, NET_ROUTER), o += 4;
    *o = 0xff;
    udp_out(at, NET_ROUTER, 67, 0xffffffffu, 68, r, sizeof(r));
}

/* ---- DNS ---- */

/* The address of `name`: 10.0.0.n for the n-th name asked. */
static uint32_t name_address(const char *name)
{
    int i;
    for (i = 0; i < wifi.name_count; i++) {
        if (strcmp(wifi.names[i], name) == 0) {
            return NET_SERVERS + 1u + (uint32_t) i;
        }
    }
    if (wifi.name_count == NAMES) {
        return NET_SERVERS + 0xfeu;
    }
    snprintf(wifi.names[i], sizeof(wifi.names[i]), "%s", name);
    wifi.name_count++;
    return NET_SERVERS + 1u + (uint32_t) i;
}

static const char *address_name(uint32_t ip)
{
    uint32_t i = ip - NET_SERVERS - 1u;
    return i < (uint32_t) wifi.name_count ? wifi.names[i] : "";
}

static void dns_in(uint64_t at, uint32_t client, uint32_t sport, const uint8_t *p, uint32_t length)
{
    char name[64];
    uint32_t n = 0, i = 12;
    if (length < 17 || (p[2] & 0x80) || get_be16(p + 4) != 1) {
        return;
    }
    while (i < length && p[i] != 0) {
        uint32_t label = p[i];
        if (label > 63 || i + 1 + label > length) {
            return;
        }
        for (uint32_t k = 0; k < label && n + 2 < sizeof(name); k++) {
            char c = (char) p[i + 1 + k];
            name[n++] = c >= 'A' && c <= 'Z' ? (char) (c - 'A' + 'a') : c;
        }
        name[n++] = '.';
        i += 1 + label;
    }
    if (i + 5 > length) {
        return;
    }
    name[n ? n - 1 : 0] = 0;
    uint32_t question = i + 5 - 12, type = get_be16(p + i + 1);
    uint8_t r[512];
    if (12 + question + 16 > sizeof(r)) {
        return;
    }
    int known = wifi.mode != MODE_NO_DNS && type == 1;
    memcpy(r, p, 2);
    be16(r + 2, known ? 0x8180 : 0x8183); /* a response, recursion; NXDOMAIN when not known */
    be16(r + 4, 1);
    be16(r + 6, known ? 1 : 0);
    be16(r + 8, 0);
    be16(r + 10, 0);
    memcpy(r + 12, p + 12, question);
    uint32_t m = 12 + question;
    if (known) {
        uint32_t ip = name_address(name);
        be16(r + m, 0xc00c);
        be16(r + m + 2, 1);
        be16(r + m + 4, 1);
        be32(r + m + 6, 300);
        be16(r + m + 10, 4);
        be32(r + m + 12, ip);
        m += 16;
        TRACE("DNS %s: %u.%u.%u.%u", name, ip >> 24, (ip >> 16) & 0xff, (ip >> 8) & 0xff, ip & 0xff);
    } else {
        TRACE("DNS %s: unknown", name);
    }
    udp_out(at, NET_ROUTER, 53, client, sport, r, m);
}

/* ---- TCP ---- */

#define TCP_FIN 0x01
#define TCP_SYN 0x02
#define TCP_RST 0x04
#define TCP_PSH 0x08
#define TCP_ACK 0x10

static void tcp_segment(uint64_t at, const Tcp *c, uint32_t seq, uint32_t flags, const uint8_t *data, uint32_t length)
{
    static uint8_t s[WIFI_FRAME_MAX];
    uint32_t header = flags & TCP_SYN ? 24 : 20;
    if (header + length > sizeof(s) - 40) {
        return;
    }
    memset(s, 0, header);
    be16(s, c->server_port);
    be16(s + 2, c->client_port);
    be32(s + 4, seq);
    be32(s + 8, flags & TCP_ACK ? c->rcv_nxt : 0);
    s[12] = (uint8_t) (header / 4 << 4);
    s[13] = (uint8_t) flags;
    be16(s + 14, TCP_IN - c->in_length);
    if (flags & TCP_SYN) {
        s[20] = 2;
        s[21] = 4;
        be16(s + 22, TCP_MSS);
    }
    memcpy(s + header, data, length);
    uint32_t sum = checksum_add(pseudo_sum(c->server_ip, NET_CLIENT, PROTO_TCP, header + length), s, header + length);
    be16(s + 16, checksum_end(sum));
    ip_out(at, PROTO_TCP, c->server_ip, NET_CLIENT, s, header + length);
}

static void tcp_reset(uint64_t at, uint32_t server_ip, const uint8_t *seg, uint32_t length)
{
    Tcp c;
    memset(&c, 0, sizeof(c));
    c.server_ip = server_ip;
    c.server_port = (uint16_t) get_be16(seg + 2);
    c.client_port = (uint16_t) get_be16(seg);
    c.rcv_nxt = get_be32(seg + 4) + length + ((seg[13] & (TCP_SYN | TCP_FIN)) ? 1 : 0);
    c.in_length = TCP_IN;
    tcp_segment(at, &c, (seg[13] & TCP_ACK) ? get_be32(seg + 8) : 0, TCP_RST | TCP_ACK, NULL, 0);
}

/* What is in `out` and fits the client's window goes out; then the FIN once all of it did. */
static void tcp_output(uint64_t at, Tcp *c, int ack)
{
    uint32_t acked = c->snd_una - (c->iss + 1);
    while (c->out_sent < c->out_length) {
        uint32_t in_flight = c->out_sent - acked, room = c->window > in_flight ? c->window - in_flight : 0;
        uint32_t n = c->out_length - c->out_sent;
        if (n > c->mss) {
            n = c->mss;
        }
        if (n > room) {
            n = room;
        }
        if (n == 0) {
            break;
        }
        tcp_segment(at, c, c->iss + 1 + c->out_sent, TCP_ACK | TCP_PSH, c->out + c->out_sent, n);
        c->out_sent += n;
        ack = 0;
    }
    if (c->closing && !c->fin_sent && c->out_sent == c->out_length) {
        tcp_segment(at, c, c->iss + 1 + c->out_sent, TCP_ACK | TCP_FIN, NULL, 0);
        c->fin_sent = 1;
        ack = 0;
    }
    if (ack) {
        tcp_segment(at, c, c->iss + 1 + c->out_sent + (uint32_t) c->fin_sent, TCP_ACK, NULL, 0);
    }
}

static void tcp_write(Tcp *c, const char *text, uint32_t length)
{
    if (c->out_length + length > TCP_OUT) {
        length = TCP_OUT - c->out_length;
    }
    memcpy(c->out + c->out_length, text, length);
    c->out_length += length;
}

static void service(Tcp *c);

static void tcp_in(uint64_t at, uint32_t server_ip, const uint8_t *seg, uint32_t length)
{
    if (length < 20) {
        return;
    }
    uint32_t sport = get_be16(seg), dport = get_be16(seg + 2), seq = get_be32(seg + 4), ack = get_be32(seg + 8);
    uint32_t offset = (uint32_t) (seg[12] >> 4) * 4, flags = seg[13];
    if (offset < 20 || offset > length) {
        return;
    }
    const uint8_t *data = seg + offset;
    uint32_t data_length = length - offset;
    Tcp *c = NULL, *free_slot = NULL;
    for (int i = 0; i < CONNECTIONS; i++) {
        Tcp *t = &wifi.tcp[i];
        if (t->state == TCP_FREE) {
            if (free_slot == NULL) {
                free_slot = t;
            }
        } else if (t->client_port == sport && t->server_port == dport && t->server_ip == server_ip) {
            c = t;
        }
    }
    if (flags & TCP_RST) {
        if (c != NULL) {
            c->state = TCP_FREE;
        }
        return;
    }
    if (flags & TCP_SYN) {
        int service_of = dport == 80 || dport == 443 ? SERVICE_HTTP : dport == 29900 ? SERVICE_GPCM : SERVICE_NONE;
        if (c != NULL) {
            c->state = TCP_FREE;
            free_slot = c;
        }
        for (int i = 0; i < CONNECTIONS && free_slot == NULL; i++) {
            if (wifi.tcp[i].fin_sent) { /* closed by this side: its slot is taken again */
                free_slot = &wifi.tcp[i];
            }
        }
        if (free_slot == NULL || service_of == SERVICE_NONE) {
            TRACE("TCP to %s port %u refused", address_name(server_ip), dport);
            tcp_reset(at, server_ip, seg, data_length);
            return;
        }
        c = free_slot;
        memset(c, 0, sizeof(*c));
        c->state = TCP_SYN_RECEIVED;
        c->service = service_of;
        c->server_ip = server_ip;
        c->client_port = (uint16_t) sport;
        c->server_port = (uint16_t) dport;
        c->rcv_nxt = seq + 1;
        c->iss = 0x10000000u * (++wifi.connections & 15u);
        c->snd_una = c->iss;
        c->window = get_be16(seg + 14);
        c->mss = 536;
        for (uint32_t i = 20; i + 1 < offset;) { /* the client's MSS */
            if (seg[i] == 0) {
                break;
            }
            if (seg[i] == 1) {
                i++;
                continue;
            }
            if (seg[i] == 2 && seg[i + 1] == 4 && i + 4 <= offset) {
                c->mss = get_be16(seg + i + 2);
            }
            if (seg[i + 1] < 2) {
                break;
            }
            i += seg[i + 1];
        }
        if (c->mss > TCP_MSS) {
            c->mss = TCP_MSS;
        }
        TRACE("TCP to %s port %u opened", address_name(server_ip), dport);
        tcp_segment(at, c, c->iss, TCP_SYN | TCP_ACK, NULL, 0);
        return;
    }
    if (c == NULL) {
        tcp_reset(at, server_ip, seg, data_length);
        return;
    }
    if (flags & TCP_ACK) {
        if (c->state == TCP_SYN_RECEIVED && ack == c->iss + 1) {
            c->state = TCP_OPEN;
            c->snd_una = ack;
        } else if (ack - c->snd_una <= c->iss + 1u + c->out_sent + (uint32_t) c->fin_sent - c->snd_una) {
            c->snd_una = ack;
        }
        c->window = get_be16(seg + 14);
    }
    if (c->state != TCP_OPEN) {
        return;
    }
    int need_ack = 0;
    if (data_length > 0) {
        need_ack = 1;
        if (seq == c->rcv_nxt) {
            uint32_t n = data_length;
            if (c->in_length + n > TCP_IN) {
                n = TCP_IN - c->in_length;
            }
            memcpy(c->in + c->in_length, data, n);
            c->in_length += n;
            c->rcv_nxt += n;
        }
    }
    if ((flags & TCP_FIN) && seq + data_length == c->rcv_nxt && !c->peer_fin) {
        c->peer_fin = 1;
        c->rcv_nxt++;
        need_ack = 1;
    }
    service(c);
    if (c->peer_fin) {
        c->closing = 1;
    }
    tcp_output(at, c, need_ack);
    if (c->fin_sent && c->peer_fin && c->snd_una == c->iss + 2u + c->out_length) {
        c->state = TCP_FREE;
    }
}

/* Called when the console connected and has not spoken yet: the services that speak first. */
static void tcp_greet(uint64_t at)
{
    for (int i = 0; i < CONNECTIONS; i++) {
        Tcp *c = &wifi.tcp[i];
        if (c->state == TCP_OPEN && !c->greeted) {
            c->greeted = 1;
            service(c);
            tcp_output(at, c, 0);
        }
    }
}

/* ---- HTTP ---- */

static const char *find(const uint8_t *p, uint32_t n, const char *what)
{
    uint32_t m = (uint32_t) strlen(what);
    for (uint32_t i = 0; i + m <= n; i++) {
        if (memcmp(p + i, what, m) == 0) {
            return (const char *) p + i;
        }
    }
    return NULL;
}

/* A header's value, lower case compared by name; "" when absent. */
static void header(const uint8_t *p, uint32_t n, const char *name, char *value, uint32_t size)
{
    uint32_t m = (uint32_t) strlen(name);
    value[0] = 0;
    for (uint32_t i = 0; i + m + 1 < n; i++) {
        if ((i == 0 || p[i - 1] == '\n')) {
            uint32_t k;
            for (k = 0; k < m; k++) {
                char a = (char) p[i + k], b = name[k];
                if (a >= 'A' && a <= 'Z') {
                    a = (char) (a - 'A' + 'a');
                }
                if (a != b) {
                    break;
                }
            }
            if (k == m && p[i + m] == ':') {
                uint32_t j = i + m + 1, v = 0;
                while (j < n && p[j] == ' ') {
                    j++;
                }
                while (j < n && p[j] != '\r' && p[j] != '\n' && v + 1 < size) {
                    value[v++] = (char) p[j++];
                }
                value[v] = 0;
                return;
            }
        }
    }
}

/* NAS's Base64: A-Z a-z 0-9 '.' '-', padded with '*'. */
static const char B64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.-";

static uint32_t b64_encode(const char *text, char *out)
{
    uint32_t n = (uint32_t) strlen(text), o = 0;
    for (uint32_t i = 0; i < n; i += 3) {
        uint32_t v = (uint32_t) (uint8_t) text[i] << 16;
        if (i + 1 < n) {
            v |= (uint32_t) (uint8_t) text[i + 1] << 8;
        }
        if (i + 2 < n) {
            v |= (uint8_t) text[i + 2];
        }
        out[o++] = B64[v >> 18 & 63];
        out[o++] = B64[v >> 12 & 63];
        out[o++] = i + 1 < n ? B64[v >> 6 & 63] : '*';
        out[o++] = i + 2 < n ? B64[v & 63] : '*';
    }
    out[o] = 0;
    return o;
}

static void b64_decode(const char *in, uint32_t n, char *out, uint32_t size)
{
    uint32_t o = 0, bits = 0, v = 0;
    for (uint32_t i = 0; i < n && in[i] != '*'; i++) {
        const char *at = strchr(B64, in[i]);
        if (at == NULL || in[i] == 0) {
            break;
        }
        v = v << 6 | (uint32_t) (at - B64);
        bits += 6;
        if (bits >= 8) {
            bits -= 8;
            if (o + 1 < size) {
                out[o++] = (char) (v >> bits & 0xff);
            }
        }
    }
    out[o] = 0;
}

/* A field of a NAS request's form body, decoded. */
static void form_field(const char *body, uint32_t n, const char *name, char *value, uint32_t size)
{
    uint32_t m = (uint32_t) strlen(name);
    value[0] = 0;
    for (uint32_t i = 0; i + m < n; i++) {
        if ((i == 0 || body[i - 1] == '&') && memcmp(body + i, name, m) == 0 && body[i + m] == '=') {
            uint32_t j = i + m + 1, k = j;
            while (k < n && body[k] != '&' && body[k] != '\r' && body[k] != '\n') {
                k++;
            }
            b64_decode(body + j, k - j, value, size);
            return;
        }
    }
}

static void http_respond(Tcp *c, const char *status, const char *type, const char *body)
{
    char head[256];
    int n = snprintf(head, sizeof(head), "HTTP/1.0 %s\r\nContent-Type: %s\r\nContent-Length: %u\r\nConnection: close\r\n\r\n",
                     status, type, (unsigned) strlen(body));
    tcp_write(c, head, (uint32_t) n);
    tcp_write(c, body, (uint32_t) strlen(body));
    c->closing = 1;
}

/* The account server's answer: each field Base64'd, joined by '&'. The token and challenge are
 * fixed; the time is the run's clock's day at noon. */
static void nas(Tcp *c, const char *body, uint32_t n)
{
    char action[32], gamecd[16], out[1024], value[160], field[256];
    form_field(body, n, "action", action, sizeof(action));
    form_field(body, n, "gamecd", gamecd, sizeof(gamecd));
    for (char *p = action; *p; p++) {
        if (*p >= 'A' && *p <= 'Z') {
            *p = (char) (*p - 'A' + 'a');
        }
    }
    wifi.nas++;
    TRACE("NAS action %s, game %s", action, gamecd);
    const char *returncd = strcmp(action, "acctcreate") == 0 ? "002" : strcmp(action, "svcloc") == 0 ? "007" : "001";
    if (wifi.mode == MODE_NAS && strcmp(action, "login") == 0) {
        returncd = "109"; /* the login refused with a code the library hands the game as an error */
    }
    const struct {
        const char *name, *value;
    } fields[] = {
        {"challenge", NAS_CHALLENGE},
        {"locator", "gamespy.com"},
        {"retry", "0"},
        {"returncd", returncd},
        {"token", "NDSACWWOFFLINETOKEN0000000000000000000000000000000000000000000000000000000000000000000000000000000"
                  "0000000000000000000000000000000"},
        {"datetime", "20260911120000"},
        {"statusdata", "Y"},
        {"svchost", "n/a"},
        {"servicetoken", "ACWWSERVICETOKEN"},
    };
    uint32_t o = 0;
    for (size_t i = 0; i < sizeof(fields) / sizeof(fields[0]); i++) {
        if (strcmp(action, "svcloc") != 0 && i >= 6) {
            break;
        }
        b64_encode(fields[i].value, value);
        int k = snprintf(field, sizeof(field), "%s%s=%s", i ? "&" : "", fields[i].name, value);
        if (k > 0 && o + (uint32_t) k + 3 < sizeof(out)) {
            memcpy(out + o, field, (size_t) k);
            o += (uint32_t) k;
        }
    }
    memcpy(out + o, "\r\n", 3);
    http_respond(c, "200 OK", "text/plain", out);
}

static void http(Tcp *c)
{
    const char *end = find(c->in, c->in_length, "\r\n\r\n");
    char host[96], length[16];
    if (end == NULL || c->closing) {
        return;
    }
    uint32_t head = (uint32_t) (end - (const char *) c->in) + 4;
    header(c->in, head, "content-length", length, sizeof(length));
    uint32_t body = (uint32_t) atoi(length);
    if (c->in_length < head + body) {
        return;
    }
    header(c->in, head, "host", host, sizeof(host));
    wifi.http++;
    TRACE("HTTP %.*s (host %s, %u bytes)", (int) (strchr((const char *) c->in, '\r') - (const char *) c->in),
          (const char *) c->in, host, body);
    if (strstr(host, "conntest.") != NULL) {
        if (wifi.mode == MODE_CONNTEST) {
            http_respond(c, "503 Service Unavailable", "text/html", "");
        } else {
            http_respond(c, "200 OK", "text/html",
                         "<html><head><title>HTML Page</title></head><body bgcolor=\"#FFFFFF\">This is test.html "
                         "page</body></html>");
        }
    } else if (strstr(host, "nas.") != NULL) {
        nas(c, (const char *) c->in + head, body);
    } else {
        http_respond(c, "404 Not Found", "text/html", "");
    }
}

/* ---- MD5 (RFC 1321), for GameSpy's login proof ---- */

static uint32_t rotl(uint32_t x, uint32_t n)
{
    return x << n | x >> (32 - n);
}

/* K[i] = floor(abs(sin(i + 1)) * 2^32) */
static const uint32_t MD5_K[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af,
    0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
    0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97,
    0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};
static const uint32_t MD5_SHIFTS[16] = {7, 12, 17, 22, 5, 9, 14, 20, 4, 11, 16, 23, 6, 10, 15, 21};

static void md5_block(uint32_t h[4], const uint8_t *p)
{
    uint32_t m[16], a = h[0], b = h[1], c = h[2], d = h[3];
    for (int i = 0; i < 16; i++) {
        m[i] =
            (uint32_t) p[4 * i] | (uint32_t) p[4 * i + 1] << 8 | (uint32_t) p[4 * i + 2] << 16 | (uint32_t) p[4 * i + 3] << 24;
    }
    for (uint32_t i = 0; i < 64; i++) {
        uint32_t f, g;
        if (i < 16) {
            f = (b & c) | (~b & d);
            g = i;
        } else if (i < 32) {
            f = (d & b) | (~d & c);
            g = (5 * i + 1) & 15;
        } else if (i < 48) {
            f = b ^ c ^ d;
            g = (3 * i + 5) & 15;
        } else {
            f = c ^ (b | ~d);
            g = (7 * i) & 15;
        }
        uint32_t t = d;
        d = c;
        c = b;
        b = b + rotl(a + f + MD5_K[i] + m[g], MD5_SHIFTS[(i / 16) * 4 + (i & 3)]);
        a = t;
    }
    h[0] += a;
    h[1] += b;
    h[2] += c;
    h[3] += d;
}

/* The MD5 of `text` in lower-case hex. */
static void md5_hex(const char *text, char out[33])
{
    uint32_t h[4] = {0x67452301u, 0xefcdab89u, 0x98badcfeu, 0x10325476u};
    uint64_t n = strlen(text), i = 0;
    uint8_t block[64];
    for (; i + 64 <= n; i += 64) {
        md5_block(h, (const uint8_t *) text + i);
    }
    uint32_t rest = (uint32_t) (n - i);
    memset(block, 0, sizeof(block));
    memcpy(block, text + i, rest);
    block[rest] = 0x80;
    if (rest >= 56) {
        md5_block(h, block);
        memset(block, 0, sizeof(block));
    }
    for (int k = 0; k < 8; k++) {
        block[56 + k] = (uint8_t) ((n * 8) >> (8 * k));
    }
    md5_block(h, block);
    for (int k = 0; k < 16; k++) {
        snprintf(out + 2 * k, 3, "%02x", (unsigned) ((h[k / 4] >> (8 * (k % 4))) & 0xff));
    }
}

/* ---- GameSpy's presence server (gpcm) ---- */

#define GPCM_CHALLENGE "ACWWOFFLIN"
#define GS_PROFILE 100000001
#define GS_USER 200000001

/* The value of `key` in a GameSpy message (\key\value\...). */
static void gs_value(const char *msg, uint32_t n, const char *key, char *value, uint32_t size)
{
    char k[40];
    snprintf(k, sizeof(k), "\\%s\\", key);
    value[0] = 0;
    const char *at = find((const uint8_t *) msg, n, k);
    if (at == NULL) {
        return;
    }
    at += strlen(k);
    uint32_t v = 0;
    while (at < msg + n && *at != '\\' && v + 1 < size) {
        value[v++] = *at++;
    }
    value[v] = 0;
}

/* A message from the console. The login is answered with the proof the library checks:
 * MD5(h + 48 spaces + the token + the server's challenge + the console's + h), h the MD5 of
 * the account server's challenge. */
static void gpcm_message(Tcp *c, const char *msg, uint32_t n)
{
    char out[1024];
    TRACE("gpcm: %.*s", (int) (n < 160 ? n : 160), msg);
    if (n > 7 && memcmp(msg, "\\login\\", 7) == 0) {
        char user_challenge[72], token[320], id[16], hash[33], text[640], proof[33];
        gs_value(msg, n, "challenge", user_challenge, sizeof(user_challenge));
        gs_value(msg, n, "authtoken", token, sizeof(token));
        gs_value(msg, n, "id", id, sizeof(id));
        md5_hex(NAS_CHALLENGE, hash);
        snprintf(text, sizeof(text), "%s%48s%s%s%s%s", hash, "", token, GPCM_CHALLENGE, user_challenge, hash);
        md5_hex(text, proof);
        int k = snprintf(out, sizeof(out),
                         "\\lc\\2\\sesskey\\1\\proof\\%s\\userid\\%d\\profileid\\%d\\uniquenick\\acwwoffline\\lt\\"
                         "ACWWOFFLINELOGINTICKET\\id\\%s\\final\\",
                         proof, GS_USER, GS_PROFILE, id[0] ? id : "1");
        tcp_write(c, out, (uint32_t) k);
    } else if (n > 12 && memcmp(msg, "\\getprofile\\", 12) == 0) {
        char id[16], profile[16];
        gs_value(msg, n, "id", id, sizeof(id));
        gs_value(msg, n, "profileid", profile, sizeof(profile));
        int k = snprintf(out, sizeof(out),
                         "\\pi\\\\profileid\\%s\\nick\\acwwoffline\\uniquenick\\acwwoffline\\email\\\\firstname\\\\"
                         "lastname\\%s\\sig\\0123456789abcdef0123456789abcdef\\id\\%s\\final\\",
                         profile[0] ? profile : "1", wifi.lastname, id[0] ? id : "1");
        tcp_write(c, out, (uint32_t) k);
    } else if (n > 11 && memcmp(msg, "\\updatepro\\", 11) == 0) {
        char lastname[sizeof(wifi.lastname)];
        gs_value(msg, n, "lastname", lastname, sizeof(lastname));
        if (lastname[0]) {
            memcpy(wifi.lastname, lastname, sizeof(lastname));
        }
    }
}

static void gpcm(Tcp *c)
{
    if (!c->greeted) {
        return;
    }
    if (c->out_length == 0) {
        const char *hello = "\\lc\\1\\challenge\\" GPCM_CHALLENGE "\\id\\1\\final\\";
        tcp_write(c, hello, (uint32_t) strlen(hello));
    }
    const char *end;
    while ((end = find(c->in, c->in_length, "\\final\\")) != NULL) {
        uint32_t n = (uint32_t) (end - (const char *) c->in) + 7;
        gpcm_message(c, (const char *) c->in, n);
        memmove(c->in, c->in + n, c->in_length - n);
        c->in_length -= n;
    }
}

static void service(Tcp *c)
{
    switch (c->service) {
        case SERVICE_HTTP:
            http(c);
            break;
        case SERVICE_GPCM:
            gpcm(c);
            break;
    }
}

/* ---- frames from the console ---- */

static void ip_in(uint64_t at, const uint8_t *p, uint32_t length)
{
    if (length < 20 || (p[0] >> 4) != 4) {
        return;
    }
    uint32_t header_length = (uint32_t) (p[0] & 15) * 4, total = get_be16(p + 2);
    if (header_length < 20 || total > length || total < header_length) {
        return;
    }
    uint32_t proto = p[9], src = get_be32(p + 12), dst = get_be32(p + 16);
    const uint8_t *data = p + header_length;
    uint32_t n = total - header_length;
    if (proto == PROTO_UDP && n >= 8) {
        uint32_t sport = get_be16(data), dport = get_be16(data + 2);
        if (dport == 67) {
            dhcp_in(at, data + 8, n - 8);
        } else if (dport == 53 && dst == NET_ROUTER) {
            dns_in(at, src, sport, data + 8, n - 8);
        } else if (dport == 27900 && n - 8 >= 5 && data[8] == 0x09) {
            /* GameSpy's availability check: the game's servers are up (status 0) */
            static const uint8_t up[7] = {0xfe, 0xfd, 0x09, 0, 0, 0, 0};
            TRACE("GameSpy availability check: up");
            udp_out(at, dst, dport, src, sport, up, sizeof(up));
        } else {
            TRACE("UDP to %s port %u, %u bytes, not answered", address_name(dst), dport, n - 8);
        }
    } else if (proto == PROTO_TCP) {
        tcp_in(at, dst, data, n);
    } else if (proto == PROTO_ICMP && n >= 8 && data[0] == 8) {
        static uint8_t e[WIFI_FRAME_MAX];
        memcpy(e, data, n);
        e[0] = 0;
        be16(e + 2, 0);
        be16(e + 2, checksum_end(checksum_add(0, e, n)));
        ip_out(at, PROTO_ICMP, dst, src, e, n);
    }
}

void wifi_send(uint64_t now, const uint8_t src[6], const uint8_t dst[6], const uint8_t *frame, uint32_t length)
{
    (void) dst;
    if (!wifi.associated || length < 8 || memcmp(frame, LLC, 6) != 0) {
        return;
    }
    memcpy(wifi.client_mac, src, 6);
    wifi.sent++;
    uint64_t at = now + LATENCY;
    uint32_t type = get_be16(frame + 6);
    if (type == ETHER_ARP) {
        arp_in(at, frame + 8, length - 8);
    } else if (type == ETHER_IP) {
        ip_in(at, frame + 8, length - 8);
    }
    tcp_greet(at);
}

/* ---- the SSL layer: plain TCP underneath ---- */

static uint32_t crc32(const uint8_t *p, uint32_t n)
{
    uint32_t crc = 0xffffffffu;
    for (uint32_t i = 0; i < n; i++) {
        crc ^= p[i];
        for (int k = 0; k < 8; k++) {
            crc = crc & 1 ? (crc >> 1) ^ 0xedb88320u : crc >> 1;
        }
    }
    return ~crc;
}

/* The SSL functions of overlay 65 (NitroWiFi 1.0.10301), each told by its code's CRC-32 (the
 * overlay shares its addresses with others), and the plain function that takes its place with
 * the same arguments: CPSi_SslRead (len, soc) -> CPSi_TcpReadRaw, CPSi_SslWrite2 (buf, len,
 * buf2, len2, soc) -> CPSi_TcpWrite2Raw, CPSi_SslConsume (len, soc) -> CPSi_SocConsumeRaw.
 * CPSi_SslConnect (soc) connects as CPSi_TcpConnectRaw unless the socket is connected already
 * (state 4, a listener's accepted socket), and the handshake is left out; CPSi_SslShutdown
 * (soc), whose only work is the close-notify alert, does nothing. The length waiting on an SSL
 * socket (CPS's function for it, named udp_read_len in the decompiled library, which the
 * socket's length function asks for an SSL socket) is the plain one: the socket's received
 * bytes (rcvbuf.size, 0x44). */
typedef struct Shim {
    uint32_t address, size, crc, plain;
    const char *name;
} Shim;

static const Shim SHIMS[] = {
    {0x0226c770u, 0x58, 0xbff9c3a8u, 0x02269eedu, "CPSi_SslConnect"},
    {0x0226c6b4u, 0xbc, 0x29e65b81u, 0x02269d49u, "CPSi_SslRead"},
    {0x0226c414u, 0xd8, 0x31c7f133u, 0x02269a6du, "CPSi_SslWrite2"},
    {0x0226c66cu, 0x48, 0x33aed333u, 0x02269cb1u, "CPSi_SslConsume"},
    {0x0226c3c0u, 0x54, 0xa2c0853fu, 0, "CPSi_SslShutdown"},
    {0x0226c4ecu, 0x7c, 0x8d2a37f2u, 0, "udp_read_len"},
};
#define SHIM_LOW 0x0226c3c0u
#define SHIM_HIGH 0x0226c770u

static void go_to(ArmCpu *cpu, uint32_t target)
{
    if (target & 1) {
        cpu->cpsr |= ARM_CPSR_T;
    } else {
        cpu->cpsr &= ~ARM_CPSR_T;
    }
    cpu->r[15] = target & ~1u;
}

static int ssl_hook(ArmCpu *cpu, void *user)
{
    const Shim *s = user;
    wifi.ssl_calls++;
    if (s == &SHIMS[0]) {
        uint32_t state = 0;
        bus_read(cpu->r[0] + 8, 1, &state);
        if (state == 4) {
            cpu->r[0] = 0;
            go_to(cpu, cpu->r[14]);
        } else {
            go_to(cpu, s->plain);
        }
    } else if (s->plain) {
        go_to(cpu, s->plain);
    } else if (s == &SHIMS[5]) {
        uint32_t length = 0;
        bus_read(cpu->r[0] + 0x44, 4, &length);
        cpu->r[0] = length;
        go_to(cpu, cpu->r[14]);
    } else {
        go_to(cpu, cpu->r[14]);
    }
    return ARM_HOOK_AGAIN;
}

ArmHook wifi_hook_at(uint32_t address, void **hook_user)
{
    if (wifi.mode == 0 || address < SHIM_LOW || address > SHIM_HIGH) {
        return NULL;
    }
    for (size_t i = 0; i < sizeof(SHIMS) / sizeof(SHIMS[0]); i++) {
        const Shim *s = &SHIMS[i];
        if (address == s->address) {
            const uint8_t *code = memory_host(address, s->size);
            if (code == NULL || crc32(code, s->size) != s->crc) {
                return NULL;
            }
            *hook_user = (void *) s;
            return ssl_hook;
        }
    }
    return NULL;
}

void wifi_report(FILE *out)
{
    if (wifi.mode == 0) {
        return;
    }
    fprintf(out,
            "wifi: %llu frames from the console, %llu to it (%llu dropped), %d names, %u TCP connections, %llu HTTP "
            "requests (%llu to NAS), %llu SSL calls taken plain\n",
            (unsigned long long) wifi.sent, (unsigned long long) wifi.received, (unsigned long long) wifi.dropped,
            wifi.name_count, wifi.connections, (unsigned long long) wifi.http, (unsigned long long) wifi.nas,
            (unsigned long long) wifi.ssl_calls);
    for (int i = 0; i < wifi.name_count; i++) {
        fprintf(out, "wifi: name %s\n", wifi.names[i]);
    }
}
