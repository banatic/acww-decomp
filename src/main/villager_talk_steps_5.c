/* villager_talk_steps_5: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02023e54 @ 0x02023e54, 0x174 bytes, Thumb
 * func_02023ddc @ 0x02023ddc, 0x78 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int a;
    int b;
} UnkStruct_02023e54;

typedef struct {
    char pad_00[0x100];
    char *unk_100;
    char unk_104[0x1e];
    u8 unk_122;
    char pad_123[9];
    int unk_12C;
    char pad_130[8];
    int unk_138;
    char pad_13C[0x40];
    UnkStruct_02023e54 unk_17C;
    char pad_184[0x18];
    u16 unk_19C;
} UnkStruct_02023e54_2;

typedef struct {
    void *p;
    u8 b;
} UnkStruct_02023e54_3;

typedef struct {
    int a, b;
} Pair;

extern int data_020c8c20;
extern UnkStruct_02023e54 data_020d8ee8;
extern int func_0208150c(int a);
extern int func_020036e8(int a);
extern int func_0200368c(void *dst, int n, int a, int b);
extern void *func_0202d9c4(UnkStruct_02023e54_2 *self);
extern int func_0209bc40(void *a);
extern void func_02063ccc(UnkStruct_02023e54 *o, int a, int b);
extern void func_020638d4(u16 *out, UnkStruct_02023e54 *o, int a, int b, int c, int d, int e);
extern void func_02063cc8(UnkStruct_02023e54 *o);
extern void func_02015de4(UnkStruct_02023e54_2 *self, void *b, int c, int d);
extern void func_0209bb90(void *a, int b);
extern void *func_02081d60(void *record);
extern int func_02081398(int a, int b);
extern int func_02099fe8(void);
extern void func_0209a088(void *, int, int);
extern void *func_020984e8(void);
extern void *func_020996ac(void *);
extern int func_0203cd2c(void *, void *, int, int);
extern int func_020154b4(void *, void *, int, int, int);
extern void func_0202dbf0(void *, Pair);
extern void func_0202dac0(void *);
extern const Pair data_020d9100;

void func_02023e54(UnkStruct_02023e54_2 *self, UnkStruct_02023e54_3 *out)
{
    void *record;
    u16 h[2];
    UnkStruct_02023e54 o1;
    UnkStruct_02023e54 o2;

    func_0200368c(&self->unk_104, 0x1e, data_020c8c20, func_020036e8(func_0208150c(*(int *) (self->unk_100 + 0x830))));
    switch (func_0209bc40(func_0202d9c4(self))) {
        case 0xe:
            self->unk_122 = 0xa;
            func_02063ccc(&o1, 0, 0);
            func_020638d4(&h[0], &o1, 0, 0, 1, 1, 0);
            self->unk_19C = h[0];
            func_02063cc8(&o1);
            func_02015de4(self, &self->unk_19C, 0, 7);
            func_0209bb90(func_0202d9c4(self), 1);
            break;
        case 0x10:
            self->unk_122 = 0xc;
            func_02063ccc(&o2, 3, 0);
            func_020638d4(&h[1], &o2, 0, 0, 1, 1, 0);
            self->unk_19C = h[1];
            func_02063cc8(&o2);
            func_02015de4(self, &self->unk_19C, 0, 7);
            func_0209bb90(func_0202d9c4(self), 1);
            break;
        case 0x11:
            if ((record = (void *) self->unk_12C) != 0 &&
                func_02081398(*(int *) (self->unk_100 + 0x830), (int) func_02081d60(record)) != 0) {
                self->unk_17C = data_020d8ee8;
                self->unk_138 = self->unk_12C;
                self->unk_122 = 0xe;
            } else {
                self->unk_122 = 0x16;
            }
            func_0209bb90(func_0202d9c4(self), 1);
            break;
        default:
            self->unk_122 = 0xa;
            break;
    }
    out->p = &self->unk_104;
    out->b = self->unk_122;
}

void func_02023ddc(void *obj)
{
    int st;

    switch (func_0209bc40((void *) ((unsigned char *) (unsigned int) func_0202d9c4((UnkStruct_02023e54_2 *) obj)))) {
        case 0xe:
        case 0x10:
            st = func_02099fe8();
            if (st >= 0) {
                func_0209a088((char *) obj + 0x19c, 0, st);
                func_0203cd2c(func_020996ac(func_020984e8()), (char *) obj + 0x19c, 0, 1);
            }
            func_020154b4(obj, (char *) obj + 0x19c, 0, 5, 0);
            func_0202dbf0(obj, data_020d9100);
            break;
        case 0x11:
            func_0202dac0(obj);
            break;
    }
}
