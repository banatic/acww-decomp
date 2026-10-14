/* PNG and SHA-1; see frame.h. */
#include "frame.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* PNG ---------------------------------------------------------------------------------- */

static uint32_t crc_table[256];

static void crc_init(void)
{
    if (crc_table[1] != 0) {
        return;
    }
    for (uint32_t n = 0; n < 256; n++) {
        uint32_t c = n;
        for (int k = 0; k < 8; k++) {
            c = (c & 1) ? 0xedb88320u ^ (c >> 1) : c >> 1;
        }
        crc_table[n] = c;
    }
}

static uint32_t crc32_update(uint32_t crc, const uint8_t *p, size_t n)
{
    crc = ~crc;
    for (size_t i = 0; i < n; i++) {
        crc = crc_table[(crc ^ p[i]) & 0xff] ^ (crc >> 8);
    }
    return ~crc;
}

static void put32(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t) (v >> 24);
    p[1] = (uint8_t) (v >> 16);
    p[2] = (uint8_t) (v >> 8);
    p[3] = (uint8_t) v;
}

/* A chunk: length, type, data, CRC over type and data. */
static int write_chunk(FILE *f, const char *type, const uint8_t *data, size_t size)
{
    uint8_t head[8], tail[4];
    put32(head, (uint32_t) size);
    memcpy(head + 4, type, 4);
    uint32_t crc = crc32_update(0, head + 4, 4);
    crc = crc32_update(crc, data, size);
    put32(tail, crc);
    return fwrite(head, 1, 8, f) == 8 && (size == 0 || fwrite(data, 1, size, f) == size) && fwrite(tail, 1, 4, f) == 4 ? 0
                                                                                                                       : -1;
}

int png_write(const char *path, const uint32_t *pixels, int width, int height)
{
    crc_init();
    /* The raw image: a filter byte (0, none) before each row of RGB. */
    size_t row = 1 + (size_t) width * 3, raw_size = row * (size_t) height;
    uint8_t *raw = malloc(raw_size);
    if (raw == NULL) {
        return -1;
    }
    for (int y = 0; y < height; y++) {
        uint8_t *r = raw + row * (size_t) y;
        *r++ = 0;
        for (int x = 0; x < width; x++) {
            uint32_t c = pixels[(size_t) y * (size_t) width + (size_t) x];
            *r++ = (uint8_t) (c >> 16);
            *r++ = (uint8_t) (c >> 8);
            *r++ = (uint8_t) c;
        }
    }
    /* zlib stream of stored blocks (65535 bytes each): header, blocks, Adler-32. */
    size_t blocks = (raw_size + 65534) / 65535;
    size_t z_size = 2 + raw_size + blocks * 5 + 4;
    uint8_t *z = malloc(z_size);
    if (z == NULL) {
        free(raw);
        return -1;
    }
    uint8_t *p = z;
    *p++ = 0x78;
    *p++ = 0x01;
    uint32_t a = 1, b = 0;
    for (size_t i = 0; i < raw_size; i++) {
        a = (a + raw[i]) % 65521;
        b = (b + a) % 65521;
    }
    for (size_t off = 0; off < raw_size || (raw_size == 0 && off == 0); off += 65535) {
        size_t n = raw_size - off < 65535 ? raw_size - off : 65535;
        *p++ = (off + n >= raw_size) ? 1 : 0;
        *p++ = (uint8_t) n;
        *p++ = (uint8_t) (n >> 8);
        *p++ = (uint8_t) ~n;
        *p++ = (uint8_t) (~n >> 8);
        memcpy(p, raw + off, n);
        p += n;
        if (raw_size == 0) {
            break;
        }
    }
    put32(p, (b << 16) | a);
    p += 4;
    free(raw);

    FILE *f = fopen(path, "wb");
    if (f == NULL) {
        free(z);
        return -1;
    }
    static const uint8_t signature[8] = {0x89, 'P', 'N', 'G', 13, 10, 26, 10};
    uint8_t ihdr[13];
    put32(ihdr, (uint32_t) width);
    put32(ihdr + 4, (uint32_t) height);
    ihdr[8] = 8; /* bit depth */
    ihdr[9] = 2; /* colour type: RGB */
    ihdr[10] = 0;
    ihdr[11] = 0;
    ihdr[12] = 0;
    int ok = fwrite(signature, 1, 8, f) == 8 && write_chunk(f, "IHDR", ihdr, 13) == 0 &&
             write_chunk(f, "IDAT", z, (size_t) (p - z)) == 0 && write_chunk(f, "IEND", NULL, 0) == 0;
    free(z);
    return fclose(f) == 0 && ok ? 0 : -1;
}

/* SHA-1 (FIPS 180-4) ----------------------------------------------------------------------- */

static uint32_t rol(uint32_t v, int n)
{
    return (v << n) | (v >> (32 - n));
}

static void sha1_block(uint32_t h[5], const uint8_t *block)
{
    uint32_t w[80];
    for (int i = 0; i < 16; i++) {
        w[i] = ((uint32_t) block[4 * i] << 24) | ((uint32_t) block[4 * i + 1] << 16) | ((uint32_t) block[4 * i + 2] << 8) |
               block[4 * i + 3];
    }
    for (int i = 16; i < 80; i++) {
        w[i] = rol(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
    }
    uint32_t a = h[0], b = h[1], c = h[2], d = h[3], e = h[4];
    for (int i = 0; i < 80; i++) {
        uint32_t f, k;
        if (i < 20) {
            f = (b & c) | (~b & d);
            k = 0x5a827999u;
        } else if (i < 40) {
            f = b ^ c ^ d;
            k = 0x6ed9eba1u;
        } else if (i < 60) {
            f = (b & c) | (b & d) | (c & d);
            k = 0x8f1bbcdcu;
        } else {
            f = b ^ c ^ d;
            k = 0xca62c1d6u;
        }
        uint32_t t = rol(a, 5) + f + e + k + w[i];
        e = d;
        d = c;
        c = rol(b, 30);
        b = a;
        a = t;
    }
    h[0] += a;
    h[1] += b;
    h[2] += c;
    h[3] += d;
    h[4] += e;
}

void sha1_hex(const void *data, size_t size, char hex[41])
{
    uint32_t h[5] = {0x67452301u, 0xefcdab89u, 0x98badcfeu, 0x10325476u, 0xc3d2e1f0u};
    const uint8_t *p = data;
    size_t off = 0;
    for (; off + 64 <= size; off += 64) {
        sha1_block(h, p + off);
    }
    uint8_t tail[128];
    size_t n = size - off;
    memcpy(tail, p + off, n);
    tail[n++] = 0x80;
    size_t total = n <= 56 ? 64 : 128;
    memset(tail + n, 0, total - n);
    uint64_t bits = (uint64_t) size * 8;
    for (int i = 0; i < 8; i++) {
        tail[total - 1 - (size_t) i] = (uint8_t) (bits >> (8 * i));
    }
    sha1_block(h, tail);
    if (total == 128) {
        sha1_block(h, tail + 64);
    }
    for (int i = 0; i < 5; i++) {
        snprintf(hex + 8 * i, 9, "%08x", h[i]);
    }
}

/* The run's frame output ------------------------------------------------------------------ */

typedef struct FrameRange {
    uint32_t first, last, step;
} FrameRange;

static const char *png_dir;
static FrameRange *png_ranges;
static int png_range_count;
static FILE *hash_out;
static uint32_t frames_output, pngs_written;
static uint8_t sequence_bytes[64 * 1024]; /* the hash lines, chained through SHA-1 */
static size_t sequence_size;
static char sequence_hex[41] = "da39a3ee5e6b4b0d3255bfef95601890afd80709"; /* SHA-1 of nothing */

/* Parses "n", "a-b" and "a-b/step" items separated by commas; unparsable items are skipped
 * with a message, so a typo does not silently save nothing. */
static void parse_ranges(const char *text)
{
    char *copy = malloc(strlen(text) + 1);
    if (copy == NULL) {
        return;
    }
    strcpy(copy, text);
    for (char *tok = strtok(copy, ","); tok != NULL; tok = strtok(NULL, ",")) {
        unsigned a, b, step = 1;
        FrameRange r;
        if (sscanf(tok, "%u-%u/%u", &a, &b, &step) == 3 || sscanf(tok, "%u-%u", &a, &b) == 2) {
            r.first = a;
            r.last = b;
        } else if (sscanf(tok, "%u", &a) == 1) {
            r.first = r.last = a;
        } else {
            fprintf(stderr, "frame: cannot read '%s' in RUN_PNG_FRAMES\n", tok);
            continue;
        }
        r.step = step ? step : 1;
        png_ranges = realloc(png_ranges, (size_t) (png_range_count + 1) * sizeof(FrameRange));
        png_ranges[png_range_count++] = r;
    }
    free(copy);
}

void frame_output_init(void)
{
    png_dir = getenv("RUN_PNG");
    const char *frames = getenv("RUN_PNG_FRAMES");
    if (frames != NULL && *frames) {
        parse_ranges(frames);
    }
    const char *hash = getenv("RUN_HASH");
    if (hash != NULL && *hash) {
        hash_out = strcmp(hash, "-") == 0 ? stdout : fopen(hash, "w");
        if (hash_out == NULL) {
            fprintf(stderr, "frame: cannot write %s\n", hash);
        }
    }
}

static int png_wanted(uint32_t frame)
{
    if (png_range_count == 0) {
        return 1;
    }
    for (int i = 0; i < png_range_count; i++) {
        const FrameRange *r = &png_ranges[i];
        if (frame >= r->first && frame <= r->last && (frame - r->first) % r->step == 0) {
            return 1;
        }
    }
    return 0;
}

/* The screen's pixels as R, G, B bytes: what the hash covers, independent of the host's
 * byte order. */
static void screen_hash(const uint32_t *pixels, char hex[41])
{
    static uint8_t rgb[256 * 192 * 3];
    for (size_t i = 0; i < 256 * 192; i++) {
        rgb[3 * i] = (uint8_t) (pixels[i] >> 16);
        rgb[3 * i + 1] = (uint8_t) (pixels[i] >> 8);
        rgb[3 * i + 2] = (uint8_t) pixels[i];
    }
    sha1_hex(rgb, sizeof(rgb), hex);
}

void frame_output(uint32_t frame, const uint32_t *upper, const uint32_t *lower)
{
    frames_output++;
    if (png_dir != NULL && *png_dir && png_wanted(frame)) {
        static uint32_t both[256 * 384];
        memcpy(both, upper, 256 * 192 * sizeof(uint32_t));
        memcpy(both + 256 * 192, lower, 256 * 192 * sizeof(uint32_t));
        char path[1024];
        snprintf(path, sizeof(path), "%s/frame-%05u.png", png_dir, frame);
        if (png_write(path, both, 256, 384) == 0) {
            pngs_written++;
        } else {
            fprintf(stderr, "frame: cannot write %s\n", path);
        }
    }
    if (hash_out != NULL) {
        char up[41], low[41];
        screen_hash(upper, up);
        screen_hash(lower, low);
        fprintf(hash_out, "frame %u %s %s\n", frame, up, low);
        /* chain: sequence = SHA-1(previous sequence, this frame's line) */
        sequence_size =
            (size_t) snprintf((char *) sequence_bytes, sizeof(sequence_bytes), "%s %u %s %s", sequence_hex, frame, up, low);
        sha1_hex(sequence_bytes, sequence_size, sequence_hex);
    }
}

void frame_report(FILE *out)
{
    if (hash_out != NULL && hash_out != stdout) {
        fflush(hash_out);
    }
    fprintf(out, "frames: %u output, %u PNGs written", frames_output, pngs_written);
    if (hash_out != NULL) {
        fprintf(out, ", sequence sha1 %s", sequence_hex);
    }
    fprintf(out, "\n");
}
