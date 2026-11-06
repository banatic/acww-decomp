/* bg_models_2: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02037af8 @ 0x02037af8, 0x1c bytes, Thumb
 * func_02037ae8 @ 0x02037ae8, 0x10 bytes, Thumb
 * func_02037ae4 @ 0x02037ae4, 0x2 bytes, Thumb
 * func_02037a40 @ 0x02037a40, 0xa4 bytes, Thumb
 * func_020379bc @ 0x020379bc, 0x84 bytes, Thumb
 * func_020379ac @ 0x020379ac, 0x10 bytes, Thumb
 * func_02037928 @ 0x02037928, 0x84 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u32 unk_00;
    u32 unk_04, unk_08, unk_0C, unk_10, unk_14, unk_18, unk_1C, unk_20;
    u32 pad_24;
    u32 unk_28, unk_2C;
} Elem1; // 0x30 bytes

typedef struct {
    u32 unk_00;
    u32 unk_04;
} Elem2; // 8 bytes

typedef struct {
    Elem1 e1[31];
    Elem2 e2[9];
    u8 unk_618;
    u8 pad_619[3];
    u32 unk_61C, unk_620, unk_624, unk_628, unk_62C;
    u32 unk_630, unk_634, unk_638, unk_63C, unk_640;
} UnkStruct_02037a40;

typedef struct {
    unsigned char pad_00[8];
    unsigned char b : 2;
    unsigned char c : 6;
} G_021ebcc8_t;

extern void *func_02064b2c(int, int, int, int);
extern int data_021c9b24;
extern int func_020b65c4(void);
extern void func_0204e938(void *);
extern void func_0205cacc(unsigned int, int);
extern void func_02037858(unsigned char *);
extern unsigned char data_020c9fd4[];
extern unsigned char data_021e9aac[];
extern unsigned int func_0204e96c(void *ptr);
extern int func_02064328(char *buf, const char *fmt, int a, int b, int c);
extern void *func_021077e8(int c);
extern int func_02056064(void *p, int a);
extern void *func_020561cc(void *p, void *q);
extern void func_020e9898(int c);
extern const char data_020da498[];
extern void *data_021fbe94;
extern G_021ebcc8_t data_021ebcc8;

void func_02037a40(UnkStruct_02037a40 *t);
void func_02037928(void *arg);

void *func_02037af8(int a, int b)
{
    return func_02064b2c(a, data_021c9b24, 4, b);
}

int func_02037ae8(int arg)
{
    func_02037a40((UnkStruct_02037a40 *) arg);
    return arg;
}

void func_02037ae4(void *object) {}

void func_02037a40(UnkStruct_02037a40 *t)
{
    Elem1 *p1;
    Elem2 *p2;
    unsigned int i;

    p1 = t->e1;
    for (i = 0; i < 31; i++) {
        p1->unk_00 = 0xffff;
        p1->unk_04 = 0;
        p1->unk_08 = 0;
        p1->unk_0C = 0;
        p1->unk_14 = 0;
        p1->unk_18 = 0;
        p1->unk_1C = 0;
        p1->unk_10 = 0;
        p1->unk_20 = 0;
        p1->unk_28 = 0;
        p1->unk_2C = 0;
        p1++;
    }

    p2 = t->e2;
    for (i = 0; i < 9; i++) {
        p2->unk_00 = 0xffff;
        p2->unk_04 = 0;
        p2++;
    }

    t->unk_630 = 0;
    t->unk_634 = 0;
    t->unk_638 = 0;
    t->unk_63C = 0;
    t->unk_640 = 0;
    t->unk_618 = 0;
    t->unk_61C = 0;
    t->unk_620 = 0;
    t->unk_624 = 0;
    t->unk_628 = 0;
    t->unk_62C = 0;
}

int func_020379bc(unsigned char *p, int param1)
{
    unsigned int idx;
    unsigned char val;

    idx = func_020b65c4();
    if (idx == 0x2c) {
        func_0204e938((void *) data_021e9aac);
    }

    func_02037a40((UnkStruct_02037a40 *) p);

    p[0x618] = (unsigned char) param1;

    idx = func_020b65c4();

    val = (unsigned char) (idx < 0x33u ? data_020c9fd4[idx] : 0xac);

    *(volatile unsigned int *) (p + 0x61c) = val << 10;
    func_0205cacc(*(volatile unsigned int *) (p + 0x61c), 0);

    if (param1 != 0 || idx == 0xb || idx == 0x2f || (unsigned char) (idx + 0xf4) <= 2) {
        func_02037928((void *) p);
    }
    if (param1 != 0) {
        func_02037858(p);
    }

    return 1;
}

unsigned int func_020379ac(void *receiver)
{
    return func_0204e96c((void *) data_021e9aac);
}

void func_02037928(void *arg)
{
    int a, b, c;
    char buf[32];

    a = func_020379ac(arg);
    b = func_020379ac(arg);
    func_02064328(buf, data_020da498, a, b, data_021ebcc8.c + 97);
    c = (int) func_02064b2c((int) buf, (int) data_021fbe94, -4, 0);
    *(void **) ((char *) arg + 0x630) = func_021077e8(c);
    func_02056064(*(void **) ((char *) arg + 0x630), 0);
    *(void **) ((char *) arg + 0x630) = func_020561cc(*(void **) ((char *) arg + 0x630), (*(void **) &data_021c9b24));
    if (c) {
        func_020e9898(c);
    }
}
