/* field_actor_room_states_22: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02229634 @ 0x02229634, 0x44 bytes, Thumb
 * func_ov004_02229614 @ 0x02229614, 0x20 bytes, Thumb
 * func_ov004_022295f8 @ 0x022295f8, 0x1c bytes, Thumb
 * func_ov004_02229530 @ 0x02229530, 0xc8 bytes, Thumb
 * func_ov004_02229510 @ 0x02229510, 0x20 bytes, Thumb
 * func_ov004_02229508 @ 0x02229508, 0x8 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02229634 {
    unsigned char b;
    unsigned char pad_01;
    short e;
};

typedef struct {
    unsigned int a;
    unsigned int b;
    short c;
} UnkStruct_022295f8;

typedef struct {
    unsigned char pad_00[0x7d4];
    UnkStruct_022295f8 sub;
} UnkStruct_022295f8_2;

extern void func_ov004_02229718(const unsigned char *a, int *c, int *d, unsigned short *e, unsigned char *b);
extern int func_ov004_02229774(int self, int c, int d, short e, int b, int f, short g);
extern void func_020110a0(void *object, short *values);
extern void func_0200fbc4(UnkStruct_022295f8_2 *self, unsigned int a, unsigned int b, short c);
extern void *data_020ccf94;
extern int func_02073908(void *, int);
extern int func_02008258(void *, int);
extern int func_02051eac(void);
extern int func_0200d4e8(void *, int, int, int);
extern int func_ov004_022294a0(void *, int, int);
extern int func_ov004_02229010(void *, int, int);
extern int func_ov004_02229258(void *, int, int);
extern void func_02010f5c(int);
extern void func_02010d64(int);

void func_ov004_02229634(char *self, short arg)
{
    struct UnkStruct_02229634 t;
    int c, d;

    func_ov004_02229718((const unsigned char *) (self + 0x8f0), &c, &d, (unsigned short *) &t.e, &t.b);
    func_ov004_02229774((int) self, c, d, t.e, t.b, 6, arg);
    return;
}

void func_ov004_02229614(char *self, int stateId)
{
    const int *src = (const int *) (self + 0x7d4);
    int *dst = (int *) (self + 0x5c);
    dst[0] = src[0];
    dst[2] = src[1];
    func_020110a0(self, (short *) (src + 2));
}

void func_ov004_022295f8(UnkStruct_022295f8_2 *self)
{
    UnkStruct_022295f8 *s;
    s = &self->sub;
    func_0200fbc4(self, s->a, s->b, s->c);
}

void func_ov004_02229530(char *self)
{
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) == 0) {
        *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
    } else {
        switch (func_02051eac()) {
            case 0:
                break;
            case 2:
                *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
                func_0200d4e8(self, 3, 1, -1);
                break;
            case 1:
            default: {
                char *a = self + 0x7d4;
                char *b = self + 0x5c;
                if (*(int *) b == *(int *) a && *(int *) (b + 8) == *(int *) (a + 4) &&
                    *(short *) (a + 8) == *(short *) (self + 0x8e)) {
                    switch (*(u8 *) (a + 0xa)) {
                        case 0:
                            func_ov004_022294a0(self, 6, -1);
                            break;
                        case 1:
                            func_ov004_02229010(self, 6, -1);
                            break;
                        case 2:
                            func_ov004_02229258(self, 6, -1);
                            break;
                    }
                }
            } break;
        }
    }
}

void func_ov004_02229510(int arg)
{
    func_ov004_022295f8((UnkStruct_022295f8_2 *) arg);
    func_02010f5c(arg);
    func_02010d64(arg);
    func_ov004_02229530((char *) arg);
}

void func_ov004_02229508(char *p, int a, int b, int c)
{
    *(int *) p = a;
    *(int *) (p + 4) = b;
    *(short *) (p + 8) = (short) c;
}
