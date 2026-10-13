/* func_02022840 @ 0x02022840, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// Filled in by func_0202e118. The halfword is volatile; it is read once per bound.
typedef struct UnkStruct_02022840 {
    volatile u16 value;
    volatile u16 unk_02;
} UnkStruct_02022840;

typedef struct UnkStruct_02022840_2 {
    u8 pad_00[0x830];
    int unk_830;
} UnkStruct_02022840_2;

typedef struct UnkStruct_02022840_3 {
    u8 pad_00[0x100];
    UnkStruct_02022840_2 *unk_100;
    u8 pad_104[0x200];
} UnkStruct_02022840_3;

typedef struct Settings {
    int unk_00;
    u8 unk_04;
} Settings;

extern Settings data_020c8b08;

extern void func_0202e118(UnkStruct_02022840 *out, UnkStruct_02022840_2 *p);
extern int func_0207f1c8(int a);
extern void func_0209b5ec(void);
extern int func_0209c330(void);
extern int func_0208150c(int a);
extern int func_020036e8(void);
extern void func_0202da38(UnkStruct_02022840_3 *self, void *a, void *b, int n, int c, int d, int e, int f, int g);

int func_02022840(UnkStruct_02022840_3 *self)
{
    int state;
    UnkStruct_02022840 info;

    state = -1;
    func_0202e118(&info, self->unk_100);
    {
        unsigned int ok = 0;
        u16 hi;
        u16 lo;

        hi = info.value;
        lo = info.value;
        if (lo >= 0x1378 && hi <= 0x1378) {
            ok = 1;
        }
        if (ok > 0) {
            state = 0;
            func_0207f1c8(self->unk_100->unk_830);
            func_0209b5ec();
            if (func_0209c330() != 5) {
                state = 2;
            }
        }
    }
    if (state != -1) {
        func_0208150c(self->unk_100->unk_830);
        func_0202da38(self, (u8 *) self + 0x104, (u8 *) self + 0x122, 0x1e, func_020036e8(), data_020c8b08.unk_00,
                      data_020c8b08.unk_04, state, 0);
        return 1;
    }
    return 0;
}
