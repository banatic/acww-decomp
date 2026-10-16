/* The owner's settings from the firmware (nickname, message, language...), read at start-up
 * from the console's flash memory through the ARM7 and copied to where the SDK's
 * OS_GetOwnerInfo finds them (0x027ffc80).
 *
 * The firmware keeps two copies of its 0x100-byte user settings, each with a save counter and
 * a CRC; the newer valid one is used. Consoles with the extended settings (iQue, DSi) also
 * carry a language that the original firmware could not store, used when the ROM's region
 * language is one of them. */
#ifndef CLEAN_MAIN_USER_SETTINGS_H
#define CLEAN_MAIN_USER_SETTINGS_H

#include "types.h"

/* One copy of the firmware's user settings; the first 0x74 bytes are the SDK's owner info. */
typedef struct UserSettingsPage {
    u8 unk_00[6];       /* version, favourite colour, birthday */
    u16 nickname[10];   /* 0x06 */
    u8 nickname_length; /* 0x1a: a 16-bit field, of which only the low byte is read */
    u8 unk_1b;
    u16 message[26];   /* 0x1c */
    u8 message_length; /* 0x50: likewise */
    u8 unk_51[0x13];   /* alarm, touch-screen calibration */
    u16 options;       /* 0x64: bits 0-2 the language */
    u8 unk_66[0x0a];   /* time zone, clock adjustment */
    u16 save_count;    /* 0x70: 0-0x7f, one more than the other copy's when newer */
    u16 crc;           /* 0x72: CRC-16 of bytes 0x00-0x6f */
    u8 ext_version;    /* 0x74: the extended settings, from here to 0xfd */
    u8 ext_language;   /* 0x75 */
    u16 ext_languages; /* 0x76: one bit per language the firmware offers */
    u8 unk_78[0x86];
    u16 ext_crc; /* 0xfe: CRC-16 of bytes 0x74-0xfd */
} UserSettingsPage;

/* What UserSettings_SelectPage found. */
enum UserSettingsChoice {
    USER_SETTINGS_NONE = 0,   /* neither copy is valid */
    USER_SETTINGS_FIRST = 1,  /* use the first copy */
    USER_SETTINGS_SECOND = 2, /* use the second copy */
    USER_SETTINGS_REFUSED = 3 /* the firmware cannot serve this ROM's region language */
};

void UserSettings_Load(void);
int UserSettings_SelectPage(UserSettingsPage *pages);
u16 UserSettings_RegionLanguages(void);
int UserSettings_HasExtension(void);
void Nvram_Read(u32 address, u32 size, void *dest);
void Nvram_OnReply(int tag, int data, int error);
void Nvram_Init(void);
void UserSettings_StartUp(void);

#endif
