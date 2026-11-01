/* Nintendo Wi-Fi Connection offline: a simulated access point, the network behind it and the
 * servers the game's library asks for, all inside the runtime (docs/multi-console.md, "Wi-Fi
 * Connection"). Nothing here touches a real network: the frames the game sends through WM's DCF
 * (runtime/wm.c) are answered by this file, at fixed emulated times, with fixed addresses,
 * sequence numbers and contents, so a run is the same on every host and in every mode.
 *
 * It is off unless RUN_WIFI is set (tools/run.py --wifi, which implies --wireless). RUN_WIFI is
 * a mode: 1 (everything answers), noap (no access point is found), nodns (every name is
 * unknown), conntest (the connection test's page answers 503), nas (the account server answers
 * with an error code).
 *
 * HTTPS is plain HTTP here: the library's SSL layer (CPS SSL in NitroWiFi, library code) is
 * replaced at its entries by the plain TCP functions it would call underneath, so a session
 * starts without a handshake and the application's bytes pass unencrypted (wifi_hook_at). No
 * game function is touched, and the same replacement applies in Reference, Native and Clean,
 * where the library runs as the ROM's code alike.
 */
#ifndef RUNTIME_WIFI_H
#define RUNTIME_WIFI_H

#include <stdint.h>
#include <stdio.h>

#include "arm.h"

#define WIFI_FRAME_MAX 1600 /* a DCF frame's body: LLC/SNAP, EtherType and the packet */
#define WIFI_BSS_SIZE 0x40  /* the access point's WMBssDesc (no game info) */
#define WIFI_ASSOCIATE_MS 20

/* Reads RUN_WIFI (with the wireless on); writes the firmware's first connection setting (the
 * access point's SSID, DHCP) into the firmware image `nvram`. Returns whether it is on. */
int wifi_init(uint8_t *nvram);
int wifi_on(void);

/* A scan of the channels `channels` (bit n-1 for channel n) for `bssid` (all 0xff: any) and the
 * first `match` bytes of `ssid` (`ssid_length` 0: any): 1 and the access point's description in
 * `desc` when it answers. */
int wifi_scan(uint32_t channels, const uint8_t bssid[6], const uint8_t *ssid, uint32_t ssid_length, uint32_t match,
              uint8_t desc[WIFI_BSS_SIZE]);
int wifi_is_ap(const uint8_t mac[6]);

/* Associated with the access point / no longer. */
void wifi_connect(uint64_t now);
void wifi_disconnect(void);

/* A frame from the console (its body as WM_SetDCFData gives it), at bus cycle `now`. */
void wifi_send(uint64_t now, const uint8_t src[6], const uint8_t dst[6], const uint8_t *frame, uint32_t length);

/* The next frame for the console whose time has come: its length (0 for none) and body, and the
 * MAC addresses it goes from and to. */
uint32_t wifi_receive(uint64_t now, uint8_t src[6], uint8_t dst[6], uint8_t *frame, uint32_t room);

/* The SSL layer's entries, when the library's overlay is in memory: the plain functions run. */
ArmHook wifi_hook_at(uint32_t address, void **hook_user);

void wifi_report(FILE *out);

#endif
