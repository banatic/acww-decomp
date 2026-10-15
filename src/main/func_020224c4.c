/* func_020224c4 @ 0x020224c4, 0x158 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct UnkStruct_020224c4 {
    u8 pad_00[0x830];
    int unk_830;
} UnkStruct_020224c4;

typedef struct UnkStruct_020224c4_2 {
    u8 pad_00[0x100];
    UnkStruct_020224c4 *unk_100;
    u8 unk_104[0x1e];
    u8 unk_122;
} UnkStruct_020224c4_2;

typedef struct Settings {
    int unk_00;
    u8 unk_04;
} Settings;

extern Settings data_020c8cc8;
extern u16 data_021dc7aa[];

extern u16 *func_02080ce4(int a);
extern int func_020984e8(void);
extern u16 *func_02099870(int a);
extern int func_02081500(int a);
extern int func_02072d4c(int a);
extern u16 *func_02072ee8(void *record);
extern int memcmp(const void *a, const void *b, unsigned int n);
extern int func_0209518c(void *a, void *b);
extern u16 *func_02095040(u16 *a);
extern void func_02015e40(UnkStruct_020224c4_2 *self, u16 *p, int n);
extern void *func_02015e70(UnkStruct_020224c4_2 *self, u16 *p, int n);
extern int func_0208150c(int a);
extern int func_020036e8(int a);
extern int func_0202da38(UnkStruct_020224c4_2 *self, void *a, void *b, int n, int c, int d, int e, int f, int g);

int func_020224c4(UnkStruct_020224c4_2 *self)
{
    int state;
    int x;
    u16 *a;
    u16 *b;
    u16 *c;
    u16 *g;
    int inner;
    volatile u16 w;

    inner = self->unk_100->unk_830;
    w = *func_02080ce4(inner);
    state = -1;
    if (func_020984e8() != 0) {
        a = func_02099870(func_020984e8());
    } else {
        a = 0;
    }

    if (a != 0) {
        unsigned int ok = 0;
        u16 hi;
        u16 lo;

        hi = w;
        lo = w;
        if (lo >= 0x12a8 && hi <= 0x12af) {
            ok = 1;
        }
        if (ok > 0) {
            x = func_02081500(inner);
            b = func_02072ee8((void *) func_02072d4c(x));
            if (*a == *b && memcmp(a + 1, b + 1, 0xc) == 0 && func_0209518c(a, b) != 0) {
                state = 1;
            } else if (func_0209518c(a, b) == 0) {
                g = data_021dc7aa;
                c = func_02095040(b);
                if (*c == *g && memcmp(c + 1, g + 1, 0xc) == 0) {
                    state = 2;
                } else {
                    state = 3;
                }
            }
            if (state != -1) {
                func_02015e40(self, func_02072ee8((void *) func_02072d4c(x)), 0);
                func_02015e70(self, func_02095040(func_02072ee8((void *) func_02072d4c(x))), 1);
            }
        } else {
            state = 0;
        }
    }

    if (state != -1) {
        func_0202da38(self, self->unk_104, &self->unk_122, 0x1e, func_020036e8(func_0208150c(self->unk_100->unk_830)),
                      data_020c8cc8.unk_00, data_020c8cc8.unk_04, state, 0);
        return 1;
    }
    return 0;
}
