/* func_020229ec @ 0x020229ec, 0xe8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020229ec {
    volatile u16 a;
    volatile u16 b;
    u16 c;
    u16 d;
} UnkStruct_020229ec;

typedef struct UnkStruct_020229ec_2 {
    u8 pad_00[0x830];
    int unk_830;
} UnkStruct_020229ec_2;

typedef struct UnkStruct_020229ec_3 {
    u8 pad_00[0x100];
    UnkStruct_020229ec_2 *unk_100;
    u8 unk_104[0x1e];
    u8 unk_122;
} UnkStruct_020229ec_3;

typedef struct Settings {
    int unk_00;
    u8 unk_04;
} Settings;

extern Settings data_020c8d40;

extern void func_0202e118(volatile u16 *out, UnkStruct_020229ec_2 *p);
extern int func_0207f1c8(int a);
extern void *func_0209b5ec(void *);
extern int func_0209c330(unsigned char *);
extern void func_0202cac4(UnkStruct_020229ec *p);
extern void func_02015de4(UnkStruct_020229ec_3 *self, UnkStruct_020229ec *p, int a, int b);
extern int func_0208150c(int a);
extern int func_020036e8(int a);
extern int func_0202da38(UnkStruct_020229ec_3 *self, void *a, void *b, int n, int c, int d, int e, int f, int g);

int func_020229ec(UnkStruct_020229ec_3 *self)
{
    int state;
    UnkStruct_020229ec info;

    state = -1;
    func_0202e118(&info.b, self->unk_100);
    {
        unsigned int ok = 0;
        u16 hi;
        u16 lo;

        hi = info.b;
        lo = info.b;
        if (lo >= 0x1374 && hi <= 0x1374) {
            ok = 1;
        }
        if (ok > 0) {
            state = 0;
            if (func_0209c330((unsigned char *) func_0209b5ec((void *) func_0207f1c8(self->unk_100->unk_830))) != 1) {
                state = 1;
            }
        }
    }
    if (state != -1) {
        info.a = 0xfff1;
        func_0202cac4(&info);
        {
            unsigned int ok2 = 0;
            u16 hi2;
            u16 lo2;

            hi2 = info.a;
            lo2 = info.a;
            if (lo2 >= 0x12e8 && hi2 <= 0x131f) {
                ok2 = 1;
            }
            if (ok2 > 0) {
                func_02015de4(self, &info, 0, 7);
                func_0202da38(self, self->unk_104, &self->unk_122, 0x1e, func_020036e8(func_0208150c(self->unk_100->unk_830)),
                              data_020c8d40.unk_00, data_020c8d40.unk_04, state, 0);
                return 1;
            }
        }
    }
    return 0;
}
