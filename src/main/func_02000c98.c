/* func_02000c98 @ 0x02000c98, 0x1f4 bytes, ARM, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UserSettingsPage;

extern void OS_InitArena(void);
extern void *OS_GetArenaHi(int id);
extern void OS_SetArenaHi(int id, void *newHi);
extern void *OS_AllocFromArenaHi(int id, u32 size, u32 align);
extern void MIi_CpuClear32(u32 data, void *destp, u32 size);
extern void MIi_CpuCopy32(const void *srcp, void *destp, u32 size);
extern void func_020010c0(unsigned int a, unsigned int b, void *c);
extern int func_02000e8c(struct UserSettingsPage *base);

void func_02000c98(void)
{
    u32 *addr;
    u32 *shift;
    u32 *cmd;
    u32 *len;
    u8 *buf;
    u8(*pages)[0x100];
    int *gen;
    int i;
    void *hi;

    OS_InitArena();
    hi = OS_GetArenaHi(0);
    addr = (u32 *) OS_AllocFromArenaHi(0, 4, 4);
    buf = (u8 *) OS_AllocFromArenaHi(0, 0x200, 0x20);
    gen = (int *) OS_AllocFromArenaHi(0, 4, 0x20);
    cmd = (u32 *) OS_AllocFromArenaHi(0, 4, 0x20);
    len = (u32 *) OS_AllocFromArenaHi(0, 4, 0x20);
    shift = (u32 *) OS_AllocFromArenaHi(0, 4, 0x20);

    *cmd = 0x20;
    *len = 2;
    *shift = 3;
    func_020010c0(*cmd, *len, addr);
    *addr <<= *shift;
    func_020010c0(*addr, 0x100, buf);
    func_020010c0(*addr + 0x100, 0x100, buf + 0x100);

    pages = (u8(*)[0x100]) buf;
    *gen = func_02000e8c((struct UserSettingsPage *) buf);
    if (*gen >= 3) {
        volatile u32 fill = 0xffffffff;
        MIi_CpuClear32(fill, (void *) 0x027ffc80, 0x74);
    } else if (*gen != 0) {
        if (*(pages[*gen] - 0xe6) < 10u) {
            for (i = 10; i > *(pages[*gen] - 0xe6); i--) {
                *(u16 *) (pages[*gen] + (i << 1) - 0xfc) = 0;
            }
        }
        if (*(pages[*gen] - 0xb0) < 26u) {
            for (i = 26; i > *(pages[*gen] - 0xb0); i--) {
                *(u16 *) (pages[*gen] + (i << 1) - 0xe6) = 0;
            }
        }
        MIi_CpuCopy32(pages[*gen] - 0x100, (void *) 0x027ffc80, 0x74);
    } else {
        volatile u32 zero = 0;
        MIi_CpuClear32(zero, (void *) 0x027ffc80, 0x74);
    }
    OS_SetArenaHi(0, hi);
}
