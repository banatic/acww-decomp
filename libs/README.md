Libraries
=========

The game links against the libraries below. Their code is not part of this repository; the
tools expect it here as `libs/<Package>/<module>/<function>.c` when it is present, and treat
those functions as not decompiled when it is not.

| Library | Version | Where the version comes from |
|---|---|---|
| NitroSDK | 3.0 (version word `0x030028a0`) | ARM9 build info block |
| NitroSystem (NNS) | not determined | no version string in the ROM |
| NitroDWC, with the GameSpy SDK | 1.0.10251 (built 2007-07-25, Korean "NOTOUCH" variant) | `[SDK+NINTENDO:DWC1.0.10251.070725.2148_DWC2005102320_NOTOUCH_KOREA]` |
| NitroWiFi, with Ubiquitous CPS and SSL | 1.0.10301 | `[SDK+NINTENDO:WiFi1.0.10301.0510201826]`, `[SDK+UBIQUITOUS:CPS]`, `[SDK+UBIQUITOUS:SSL]` |
| NitroSDK backup library | (with NitroSDK) | `[SDK+NINTENDO:BACKUP]` |
| Metrowerks MSL C library and runtime | CodeWarrior for DS 1.2 | the compiler the game was built with |

In this ROM they account for 4,083 functions, about 590 KB of the ARM9 code (`autoload_2`,
`itcm`, the start of `main`, `ov001`, `ov065` and `ov067`).
