/* music_list_input_5: 9 functions, module ov144
 * mwccarm 1.2/base -O4,s
 * func_ov144_0229a824 @ 0x0229a824, 0x16 bytes, Thumb
 * func_ov144_0229a7e8 @ 0x0229a7e8, 0x3a bytes, Thumb
 * func_ov144_0229a7c8 @ 0x0229a7c8, 0x20 bytes, Thumb
 * func_ov144_0229a798 @ 0x0229a798, 0x30 bytes, Thumb
 * func_ov144_0229a71c @ 0x0229a71c, 0x7c bytes, Thumb
 * func_ov144_0229a6c8 @ 0x0229a6c8, 0x54 bytes, Thumb
 * func_ov144_0229a5f4 @ 0x0229a5f4, 0xd4 bytes, Thumb
 * func_ov144_0229a5bc @ 0x0229a5bc, 0x36 bytes, Thumb
 * func_ov144_0229a588 @ 0x0229a588, 0x34 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229a71c {
    unsigned char pad_00[0xba];      // 0x00
    short unk_BA;                    // 0xba
    short unk_BC;                    // 0xbc
    unsigned char pad_BE[2];         // 0xbe
    unsigned char unk_C0;            // 0xc0
    unsigned char pad_C1[0x7ab];     // 0xc1
    unsigned short array_86c[0x400]; // 0x86c
};

typedef struct {
    char pad_00[0xba];
    s16 unk_BA;
    s16 unk_BC;
    char pad_BE[2];
    u8 unk_C0;
    char pad_C1[0x86c - 0xc1];
    u16 arr[4];
} UnkStruct_0229a5f4;

extern void func_ov144_0229a17c(void *arg0);
extern unsigned char *func_ov002_02208098(void *p, unsigned char n);
extern int func_ov144_02299680(void *p, int n);
extern void func_ov144_02299660(void *p, int n);
extern void func_ov144_0229a264(void *p);
extern void func_ov002_02207fc0(void *p);
extern int func_0206fe60(void);
extern void func_0206fc4c(int);
extern void *func_ov002_0220a720(void *, int);
extern void func_ov002_02208090(void *, int);
extern void func_ov144_02299c5c(struct UnkStruct_0229a71c *p, int a);
extern void func_ov144_02299694(struct UnkStruct_0229a71c *p, int a);
extern void func_0206f674(int a);
extern void func_0200467c(int cmd);
extern unsigned char data_020e54a8;
extern int func_ov004_0223c310(void);
extern void func_ov144_02299670(void *p, int n);
extern void func_ov144_02299b7c(void *p);
extern int func_02060a98(volatile u16 *p);
extern int func_02099fe8(void);
extern void func_0209a088(volatile u16 *p, int a, int b);
extern void func_02060984(unsigned int item);
extern void func_ov144_02299c2c(UnkStruct_0229a5f4 *self, int a);
extern void func_ov144_02299bfc(void *p, int n);
extern int func_ov002_0220b9b8(void *a, void *b, int c, int d);
extern void func_0208e5c4(void *a);

void func_ov144_0229a6c8(void *p);
void func_ov144_0229a588(void *a, char b);

unsigned char *func_ov144_0229a824(void *p)
{
    func_ov144_0229a17c((void *) p);
    return func_ov002_02208098(p, 0);
}

unsigned char *func_ov144_0229a7e8(void *self)
{
    if (func_ov144_02299680(self, 0x10)) {
        func_ov144_02299660(self, 0x10);
    } else {
        *((char *) self + 0xc1) = 0xb;
    }
    func_ov144_0229a264(self);
    func_ov002_02207fc0(self);
    return func_ov002_02208098(self, 3);
}

int func_ov144_0229a7c8(int a)
{
    if (func_0206fe60()) {
        return (int) func_ov144_0229a824((void *) a);
    } else {
        return (int) func_ov144_0229a7e8((void *) a);
    }
}

void func_ov144_0229a798(void *self)
{
    func_0206fc4c(0);
    func_ov002_0220a720((char *) self + 0x170, 6);
    func_ov002_02208090(self, 2);
    func_ov002_02208098(self, 9);
}

int func_ov144_0229a71c(struct UnkStruct_0229a71c *p)
{
    if (p->unk_BA == -1) {
        return 0;
    }

    if (p->unk_BC != -1) {
        func_ov144_0229a6c8((void *) p);
        return 0;
    }

    func_ov144_02299660((void *) p, 0x20);
    p->unk_C0 = 5;
    func_ov144_02299c5c(p, 8);
    func_ov002_02208098((void *) p, 0xb);
    func_ov144_02299694(p, p->unk_BA);
    func_0206fc4c(1);
    func_0206f674(p->array_86c[p->unk_BA]);
    func_ov002_02208090((void *) p, 2);
    func_0200467c(0x55);
    return 1;
}

void func_ov144_0229a6c8(void *p)
{
    int flag;
    short *field;

    flag = data_020e54a8 ? 0 : 1;
    if (flag == 0) {
        func_ov004_0223c310();
    }
    func_ov144_02299694((struct UnkStruct_0229a71c *) p, (short) (*(short *) ((char *) p + 0xbc)));
    field = (short *) ((char *) p + 0xbc);
    *field = -1;
    func_ov144_02299670(p, 8);
    func_ov144_02299b7c(p);
    func_ov144_0229a7c8((int) p);
    func_0200467c(0x56);
}

int func_ov144_0229a5f4(UnkStruct_0229a5f4 *self)
{
    volatile u16 t;
    int r;
    unsigned int ok;

    if (self->unk_BA == -1) {
        return 0;
    }
    t = self->arr[self->unk_BA];
    if (func_02060a98(&t) != 0) {
        func_ov144_0229a588((void *) self, 0x20);
        return 1;
    }
    r = func_02099fe8();
    if (r == -1) {
        func_ov144_0229a588((void *) self, 0x10);
        return 1;
    }
    func_0209a088(&t, 0, r);
    if (self->unk_BA == self->unk_BC) {
        ok = ((*(u8 *) &data_020e54a8) == 0) ? 1 : 0;
        if (ok == 0) {
            func_ov004_0223c310();
        }
        self->unk_BC = -1;
    }
    func_02060984(self->arr[self->unk_BA]);
    func_ov144_02299694((struct UnkStruct_0229a71c *) self, self->unk_BA);
    self->unk_C0 = 0xa;
    func_ov144_02299c2c(self, 8);
    func_ov002_02208098((void *) self, 0xa);
    func_ov144_02299670((void *) self, 0x10);
    func_0200467c(0x58);
    return 1;
}

void func_ov144_0229a5bc(void *param0)
{
    func_ov144_02299670(param0, 0x20);
    func_ov144_02299bfc(param0, 8);
    ((unsigned char *) param0)[0xC0] = 5;
    func_ov002_02208098(param0, 0xB);
    func_ov002_02208090(param0, 2);
    func_0200467c(0x57);
}

void func_ov144_0229a588(void *a, char b)
{
    char c;
    void *p;
    c = b;
    p = (char *) a + 0x750;
    func_ov002_0220b9b8(p, &c, 1, 0);
    func_ov002_02208098(a, 0xc);
    func_0208e5c4((char *) a + 0xc4);
}
