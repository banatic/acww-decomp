/* func_02022ad4 @ 0x02022ad4, 0xe8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02022ad4 {
    volatile u16 a;
    volatile u16 b;
    u16 c;
    u16 d;
} UnkStruct_02022ad4;

typedef struct UnkStruct_02022ad4_2 {
    u8 pad_00[0x830];
    int unk_830;
} UnkStruct_02022ad4_2;

typedef struct UnkStruct_02022ad4_3 {
    u8 pad_00[0x100];
    UnkStruct_02022ad4_2 *unk_100;
    u8 unk_104[0x1e];
    u8 unk_122;
} UnkStruct_02022ad4_3;

typedef struct Settings {
    int unk_00;
    u8 unk_04;
} Settings;

extern Settings data_020c8b48;

extern void func_0202e118(volatile u16 *out, UnkStruct_02022ad4_2 *p);
extern int func_0207f1c8(int a);
extern void func_0209b5ec(void);
extern int func_0209c330(void);
extern void func_0202cfa8(UnkStruct_02022ad4 *p);
extern void func_02015de4(UnkStruct_02022ad4_3 *self, UnkStruct_02022ad4 *p, int a, int b);
extern int func_0208150c(int a);
extern int func_020036e8(int a);
extern void func_0202da38(UnkStruct_02022ad4_3 *self, void *a, void *b, int n, int c, int d, int e, int f, int g);

int func_02022ad4(UnkStruct_02022ad4_3 *self)
{
    int state;
    UnkStruct_02022ad4 info;

    state = -1;
    func_0202e118(&info.b, self->unk_100);
    {
        unsigned int ok = 0;
        u16 hi;
        u16 lo;

        hi = info.b;
        lo = info.b;
        if (lo >= 0x1376 && hi <= 0x1376) {
            ok = 1;
        }
        if (ok > 0) {
            state = 0;
            func_0207f1c8(self->unk_100->unk_830);
            func_0209b5ec();
            if (func_0209c330() != 0) {
                state = 2;
            }
        }
    }
    if (state != -1) {
        info.a = 0xfff1;
        func_0202cfa8(&info);
        {
            unsigned int ok2 = 0;
            u16 hi2;
            u16 lo2;

            hi2 = info.a;
            lo2 = info.a;
            if (lo2 >= 0x12b0 && hi2 <= 0x12e7) {
                ok2 = 1;
            }
            if (ok2 > 0) {
                func_02015de4(self, &info, 0, 7);
                func_0202da38(self, self->unk_104, &self->unk_122, 0x1e, func_020036e8(func_0208150c(self->unk_100->unk_830)),
                              data_020c8b48.unk_00, data_020c8b48.unk_04, state, 0);
                return 1;
            }
        }
    }
    return 0;
}
