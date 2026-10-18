/* The owner's settings from the firmware (user_settings.h). */
#include "user_settings.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"

static_assert(offsetof(UserSettingsPage, nickname_length) == 0x1a, "UserSettingsPage layout");
static_assert(offsetof(UserSettingsPage, message_length) == 0x50, "UserSettingsPage layout");
static_assert(offsetof(UserSettingsPage, options) == 0x64, "UserSettingsPage layout");
static_assert(offsetof(UserSettingsPage, save_count) == 0x70, "UserSettingsPage layout");
static_assert(offsetof(UserSettingsPage, ext_languages) == 0x76, "UserSettingsPage layout");
static_assert(sizeof(UserSettingsPage) == 0x100, "UserSettingsPage layout");

#define OS_ARENA_MAIN 0
#define OWNER_INFO ((void *) 0x027ffc80) /* the SDK's copy of the owner's settings */
#define OWNER_INFO_SIZE 0x74
#define ROM_HEADER_REGION (*(const u8 *) 0x027ffe1d) /* the loaded ROM header's region byte */

#define FIRMWARE_CONSOLE_TYPE 0x1d    /* firmware header: 0xff DS, 0x20 DS Lite, 0x43/0x63 iQue */
#define FIRMWARE_SETTINGS_OFFSET 0x20 /* firmware header: where the user settings are, in 8 bytes */

#define LANGUAGE_CHINESE (1 << 6)
#define LANGUAGE_KOREAN (1 << 7)
#define OPTIONS_LANGUAGE 0x7

#define PXI_FIFO_TAG_NVRAM 4
#define PXI_PROC_ARM7 1
#define NVRAM_READ_COMMAND 0x23
/* The request is six words: an index in bits 16-23, the first marked as the start and the last
 * as the end of the request. */
#define NVRAM_WORD_START 0x02000000u
#define NVRAM_WORD_END 0x01000000u
#define NVRAM_WORD(index) ((u32) (index) << 16)

enum NvramReply { NVRAM_REPLY_WAITING = 0, NVRAM_REPLY_DONE = 1, NVRAM_REPLY_FAILED = 2 };

#define REG_IME (*(volatile u16 *) 0x04000208)

extern void OS_Init(void);
extern void OS_InitArena(void);
extern void *OS_GetArenaHi(int id);
extern void OS_SetArenaHi(int id, void *hi);
extern void *OS_AllocFromArenaHi(int id, u32 size, u32 align);
extern void MIi_CpuClear32(u32 data, void *dest, u32 size);
extern void MIi_CpuCopy32(const void *src, void *dest, u32 size);
extern u16 GetCRC16(u16 start, const void *data, u32 size);
extern void DC_InvalidateRange(void *start, u32 size);
extern void OS_SpinWait(u32 cycles);
extern int PXI_SendWordByFifo(int tag, u32 data, BOOL error);
extern BOOL PXI_IsCallbackReady(int tag, int proc);
extern void PXI_SetFifoRecvCallback(int tag, void (*callback)(int tag, int data, int error));

/* Nvram_Read and Nvram_Init wait on the FIFO interrupt, so the runtime keeps the ROM's code for
 * them (runtime/native-reference.txt) and they are called through their DS addresses. The
 * reply callback is installed by its DS address: Nvram_OnReply is its Clean version. */
extern void func_02001238(int tag, int data, int error);

/* NvramReply of the last request; written by the FIFO interrupt. */
extern volatile s32 data_0213fdc0;

/* An ARM shift by a register amount: amounts of 32 and more give 0. */
static u32 shift_left(u32 value, u32 amount)
{
    return amount < 32 ? value << amount : 0;
}

/* func_02000c98: read the firmware's user settings and put the newer valid copy where the SDK
 * keeps the owner's settings; all 0xff when the firmware refuses this ROM's language, all
 * zero when no copy is valid. The work buffers come from the main arena's top and are given
 * back at the end. The nickname and message are cleared after their length. */
void UserSettings_Load(void)
{
    void *arena_hi;
    u32 *settings_address;
    UserSettingsPage *pages;
    int *choice;
    u32 *header_offset;
    u32 *header_size;
    u32 *scale;
    int i;

    OS_InitArena();
    arena_hi = OS_GetArenaHi(OS_ARENA_MAIN);
    settings_address = OS_AllocFromArenaHi(OS_ARENA_MAIN, 4, 4);
    pages = OS_AllocFromArenaHi(OS_ARENA_MAIN, 2 * sizeof(UserSettingsPage), 0x20);
    choice = OS_AllocFromArenaHi(OS_ARENA_MAIN, 4, 0x20);
    header_offset = OS_AllocFromArenaHi(OS_ARENA_MAIN, 4, 0x20);
    header_size = OS_AllocFromArenaHi(OS_ARENA_MAIN, 4, 0x20);
    scale = OS_AllocFromArenaHi(OS_ARENA_MAIN, 4, 0x20);

    /* QUIRK: the firmware header field's offset, size and scale are kept in arena words, which
     * are written here and read back. */
    *header_offset = FIRMWARE_SETTINGS_OFFSET;
    *header_size = 2;
    *scale = 3;
    Nvram_Read(*header_offset, *header_size, settings_address);
    *settings_address <<= *scale;
    Nvram_Read(*settings_address, sizeof(UserSettingsPage), &pages[0]);
    Nvram_Read(*settings_address + sizeof(UserSettingsPage), sizeof(UserSettingsPage), &pages[1]);

    *choice = UserSettings_SelectPage(pages);
    if (*choice >= USER_SETTINGS_REFUSED) {
        MIi_CpuClear32(0xffffffff, OWNER_INFO, OWNER_INFO_SIZE);
    } else if (*choice != USER_SETTINGS_NONE) {
        UserSettingsPage *page = &pages[*choice - 1];
        /* cleared from the end down to the length, as the original does */
        for (i = 10; i > page->nickname_length; i--) {
            page->nickname[i - 1] = 0;
        }
        for (i = 26; i > page->message_length; i--) {
            page->message[i - 1] = 0;
        }
        MIi_CpuCopy32(page, OWNER_INFO, OWNER_INFO_SIZE);
    } else {
        MIi_CpuClear32(0, OWNER_INFO, OWNER_INFO_SIZE);
    }
    OS_SetArenaHi(OS_ARENA_MAIN, arena_hi);
}
CLEAN_AS(func_02000c98, UserSettings_Load)

/* Whether a copy's first part (the SDK's settings) is intact. */
static BOOL page_is_valid(const UserSettingsPage *page)
{
    return GetCRC16(0xffff, page, 0x70) == page->crc && page->save_count < 0x80;
}

/* func_02000e8c: which of the two copies to use (UserSettingsChoice). With the extended
 * settings, a copy must also have its extension intact and offer its own language; its
 * language then replaces the SDK's when the firmware offers this ROM's region language. A
 * Chinese ROM is refused by a firmware that does not offer Chinese. When both copies are
 * valid, the second is used if its counter is one more than the first's. */
int UserSettings_SelectPage(UserSettingsPage *pages)
{
    int valid = 0;
    int i;

    if (UserSettings_HasExtension()) {
        u16 region = UserSettings_RegionLanguages();
        for (i = 0; i < 2; i++) {
            UserSettingsPage *page = &pages[i];
            if (!page_is_valid(page)) {
                continue;
            }
            if (GetCRC16(0xffff, &page->ext_version, 0x8a) != page->ext_crc) {
                continue;
            }
            if ((shift_left(1, page->ext_language) & page->ext_languages) == 0) {
                continue;
            }
            if ((region & page->ext_languages) != 0) {
                page->options = (u16) ((page->options & ~OPTIONS_LANGUAGE) | (page->ext_language & OPTIONS_LANGUAGE));
            }
            if ((region & LANGUAGE_CHINESE & ~page->ext_languages) != 0) {
                return USER_SETTINGS_REFUSED;
            }
            valid |= 1 << i;
        }
    } else {
        if ((UserSettings_RegionLanguages() & LANGUAGE_CHINESE) != 0) {
            return USER_SETTINGS_REFUSED;
        }
        for (i = 0; i < 2; i++) {
            if (page_is_valid(&pages[i])) {
                valid |= 1 << i;
            }
        }
    }

    switch (valid) {
        case 1:
            return USER_SETTINGS_FIRST;
        case 2:
            return USER_SETTINGS_SECOND;
        case 3:
            if (((pages[0].save_count + 1) & 0x7f) == pages[1].save_count) {
                return USER_SETTINGS_SECOND;
            }
            return USER_SETTINGS_FIRST;
        default:
            return USER_SETTINGS_NONE;
    }
}
CLEAN_AS(func_02000e8c, UserSettings_SelectPage)

/* func_0200103c: the language this ROM's region needs as a bit of ext_languages: Chinese for
 * a Chinese ROM (region 0x80), Korean for a Korean one (0x40), none otherwise. */
u16 UserSettings_RegionLanguages(void)
{
    switch (ROM_HEADER_REGION) {
        case 0x80:
            return LANGUAGE_CHINESE;
        case 0x40:
            return LANGUAGE_KOREAN;
        default:
            return 0;
    }
}
CLEAN_AS(func_0200103c, UserSettings_RegionLanguages)

/* func_02001074: whether the firmware has the extended settings, from its console type
 * (bits 0x50; 0xff, an original DS, has none). The byte is read into a buffer from the main
 * arena's top that is not given back here (UserSettings_Load restores the arena). */
int UserSettings_HasExtension(void)
{
    u8 *type = OS_AllocFromArenaHi(OS_ARENA_MAIN, 1, 0x20);
    Nvram_Read(FIRMWARE_CONSOLE_TYPE, 1, type);
    if (*type == 0xff) {
        return 0;
    }
    return (*type & 0x50) != 0;
}
CLEAN_AS(func_02001074, UserSettings_HasExtension)

/* Sends the six words of a request; FALSE as soon as the FIFO refuses one. */
static BOOL send_request(const u32 words[6])
{
    int i;

    for (i = 0; i < 6; i++) {
        if (PXI_SendWordByFifo(PXI_FIFO_TAG_NVRAM, words[i], FALSE) < 0) {
            return FALSE;
        }
    }
    return TRUE;
}

/* func_020010c0: read `size` bytes at `address` of the firmware's flash into `dest`, through
 * the ARM7, and wait for them; a request the ARM7 reports as failed is made again, and one
 * the FIFO refuses is sent again from its first word after a pause.
 * HW: the reply is written by the FIFO interrupt (Nvram_OnReply) while this waits.
 * QUIRK: only the first 32 bytes of `dest` are invalidated in the data cache, whatever the
 * size. */
void Nvram_Read(u32 address, u32 size, void *dest)
{
    u32 words[6];

    words[0] = NVRAM_WORD_START | NVRAM_WORD(0) | NVRAM_READ_COMMAND << 8 | ((address >> 16) & 0xff);
    words[1] = NVRAM_WORD(1) | (address & 0xffff);
    words[2] = NVRAM_WORD(2) | size >> 16;
    words[3] = NVRAM_WORD(3) | (size & 0xffff);
    words[4] = NVRAM_WORD(4) | (u32) (uintptr_t) dest >> 16;
    words[5] = NVRAM_WORD_END | NVRAM_WORD(5) | ((u32) (uintptr_t) dest & 0xffff);

    for (;;) {
        data_0213fdc0 = NVRAM_REPLY_WAITING;
        DC_InvalidateRange(dest, 0x20);
        while (!send_request(words)) {
            OS_SpinWait(100000);
        }
        while (data_0213fdc0 == NVRAM_REPLY_WAITING) {
        }
        if (data_0213fdc0 == NVRAM_REPLY_DONE) {
            return;
        }
    }
}
CLEAN_AS(func_020010c0, Nvram_Read)

/* func_02001238: the FIFO callback for the ARM7's replies: done when the transfer had no
 * error and the reply's low byte is 0, failed otherwise. */
void Nvram_OnReply(int tag, int data, int error)
{
    (void) tag;
    if (error == 0 && (data & 0xff) == 0) {
        data_0213fdc0 = NVRAM_REPLY_DONE;
    } else {
        data_0213fdc0 = NVRAM_REPLY_FAILED;
    }
}
CLEAN_AS(func_02001238, Nvram_OnReply)

/* func_02001268: wait for the ARM7 to listen on the NVRAM FIFO channel, install the reply
 * callback and enable interrupts.
 * HW: the master interrupt enable is read (the value is dropped) and then set to 1. */
void Nvram_Init(void)
{
    u16 previous;

    while (!PXI_IsCallbackReady(PXI_FIFO_TAG_NVRAM, PXI_PROC_ARM7)) {
    }
    PXI_SetFifoRecvCallback(PXI_FIFO_TAG_NVRAM, func_02001238);
    previous = REG_IME;
    (void) previous;
    REG_IME = 1;
}
CLEAN_AS(func_02001268, Nvram_Init)

/* func_020012bc: the start-up hook (NitroStartUp): initialise the OS, then load the owner's
 * settings. */
void UserSettings_StartUp(void)
{
    OS_Init();
    Nvram_Init();
    UserSettings_Load();
}
CLEAN_AS(func_020012bc, UserSettings_StartUp)
