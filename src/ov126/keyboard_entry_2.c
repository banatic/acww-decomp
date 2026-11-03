/* keyboard_entry_2: 17 functions, module ov126
 * mwccarm 1.2/base -O4,s
 * func_ov126_0229fc98 @ 0x0229fc98, 0x40 bytes, Thumb
 * func_ov126_0229fc7c @ 0x0229fc7c, 0x1c bytes, Thumb
 * func_ov126_0229fc54 @ 0x0229fc54, 0x28 bytes, Thumb
 * func_ov126_0229fc34 @ 0x0229fc34, 0x20 bytes, Thumb
 * func_ov126_0229fc14 @ 0x0229fc14, 0x20 bytes, Thumb
 * func_ov126_0229fb9c @ 0x0229fb9c, 0x78 bytes, Thumb
 * func_ov126_0229fb58 @ 0x0229fb58, 0x44 bytes, Thumb
 * func_ov126_0229fb10 @ 0x0229fb10, 0x48 bytes, Thumb
 * func_ov126_0229fa80 @ 0x0229fa80, 0x90 bytes, Thumb
 * func_ov126_0229fa38 @ 0x0229fa38, 0x48 bytes, Thumb
 * func_ov126_0229f9b8 @ 0x0229f9b8, 0x80 bytes, Thumb
 * func_ov126_0229f9a0 @ 0x0229f9a0, 0x18 bytes, Thumb
 * func_ov126_0229f968 @ 0x0229f968, 0x38 bytes, Thumb
 * func_ov126_0229f930 @ 0x0229f930, 0x38 bytes, Thumb
 * func_ov126_0229f90c @ 0x0229f90c, 0x24 bytes, Thumb
 * func_ov126_0229f8e8 @ 0x0229f8e8, 0x24 bytes, Thumb
 * func_ov126_0229f83c @ 0x0229f83c, 0xaa bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x4248];
    char data[10];
} UnkStruct_0229fc98;

struct UnkStruct_0229fb10 {
    unsigned char pad_00[0xa6];
    unsigned char unk_A6;
    char pad_A7[0x4248 - 0xa7];
    char unk_4248;
};

typedef struct {
    u32 data[10];
} UnkStruct_0229fa80;

typedef struct {
    u32 data[28];
} UnkStruct_0229fa80_2;

typedef struct {
    char pad_00[0xa6];
    unsigned char unk_A6;
    char pad_A7[0x4248 - 0xa7];
    char unk_4248;
} UnkStruct_0229fa38;

typedef struct {
    char pad_00[0x4248];
    int unk_4248;
} UnkStruct_0229f968;

extern int func_020984e8(void);
extern int func_020996b8(int object);
extern int func_0206fc8c(void);
extern int func_02072bb0(int a, int b);
extern int func_02072d4c(unsigned int argument0);
extern void func_02072e90(int a, void *ptr);
extern void func_02051c08(void *dst, const void *src, int len);
extern void func_020b13e4(const void *p, int value);
extern int func_02099658(int argument0);
extern void *func_02077d00(void *entries);
extern int func_02077c34(int arg);
extern char *func_02077c38(char *);
extern int func_0206fca4(void);
extern int func_0206fc44(void);
extern void func_02072e3c(unsigned int, unsigned char *);
extern void *func_02070c08(void *p);
extern void func_02070934(void *p, const void *data, int n);
extern int func_020707e8(void *p, void *arg, unsigned char b);
extern void func_0206fc4c(int x);
extern int **func_02070be8(void *p);
extern unsigned char data_ov126_022a2134[];
extern void *func_02062fbc(void *);
extern int func_02062ea4(void *, u16 const *);
extern void *func_020a8bb8(void *, void *);
extern void func_0206fc80(int);
extern void *func_02062f4c(void *);
extern const char data_ov126_022a2128[];
extern int func_02099870(int);
extern int func_0209871c(int, int);
extern int func_020988a4(int, int);
extern int func_02098844(int, int);
extern int func_020950a8(int);
extern int func_02051bb4(int, void *, int);
extern void func_020950ac(int, void *);
extern char data_021dc7bc[];
extern void func_02064244(void *a, void *b);
extern unsigned char data_021dc7aa[];
extern int func_020b1078(void *, void *);
extern void func_020b141c(void *, void *);
extern void *func_02088220(void *record);
extern unsigned char data_021f3278[];
extern void func_ov126_0229f7dc(int);

void func_ov126_0229fc98(UnkStruct_0229fc98 *param)
{
    char buf[20];
    int a, b, c;
    a = func_020996b8(func_020984e8());
    b = func_0206fc8c();

    c = func_02072d4c((unsigned int) func_02072bb0(a, b));
    func_02072e90(c, buf);
    func_02051c08(buf, param->data, 10);
}

void func_ov126_0229fc7c(char *p)
{
    func_020b13e4(p + 0x4248, func_0206fc8c());
}

int func_ov126_0229fc54(void)
{
    int base;
    int index;
    int result;

    base = func_02099658((int) func_020984e8());
    index = func_0206fc8c();
    result = (int) func_02077d00((void *) base);
    result += index * 0x24;
    return result;
}

void func_ov126_0229fc34(int *obj)
{
    int a;
    int b;
    a = func_ov126_0229fc54();
    b = func_02077c34(a);
    func_02051c08((void *) b, (const void *) ((void *) ((char *) obj + 0x4248)), 6);
}

void func_ov126_0229fc14(char *p)
{
    char *q = (char *) func_ov126_0229fc54();
    char *r = func_02077c38(q);
    func_02051c08((void *) r, (const void *) (p + 0x4248), 6);
}

void func_ov126_0229fb9c(unsigned char *arg0)
{
    switch (func_0206fca4() - 11) {
        case 6:
        case 10:
        case 11:
        case 12:
            func_02051c08((void *) (func_0206fc44()), (const void *) ((unsigned char *) arg0 + 0x4248), (unsigned char) arg0[0xa6]);
            break;
        case 0:
            func_ov126_0229fc98((UnkStruct_0229fc98 *) arg0);
            break;
        case 7:
            func_ov126_0229fc7c((char *) arg0);
            break;
        case 13:
        case 14:
            func_ov126_0229fc34((int *) arg0);
            break;
        case 15:
        case 16:
            func_ov126_0229fc14((char *) arg0);
            break;
        default:
            break;
    }
}

void func_ov126_0229fb58(void *self)
{
    unsigned char buf[0x14];
    unsigned int v;

    v = (unsigned int) func_02072bb0((unsigned int) func_020996b8(func_020984e8()), (unsigned int) func_0206fc8c());
    func_02051c08((void *) ((unsigned char *) self + 0x4248), (const void *) buf, 10);
    func_02072e3c((unsigned int) func_02072d4c(v), buf);
}

void func_ov126_0229fb10(struct UnkStruct_0229fb10 *self)
{
    char local[0x70];
    int ret;

    func_02070c08(&local);
    ret = func_0206fc8c();
    func_02070934(&local, (void *) data_ov126_022a2134, ret);
    if (func_020707e8(&local, &self->unk_4248, self->unk_A6) == 0) {
        func_0206fc4c(0);
    }
    func_02070be8(&local);
}

void func_ov126_0229fa80(u8 *param)
{
    UnkStruct_0229fa80 obj1;
    UnkStruct_0229fa80_2 obj2;
    u16 i;
    u16 idx;

    func_02062fbc(&obj1);
    func_02070c08(&obj2);

    i = 0x1323;
    while (i <= 0x1368u) {
        idx = i;
        func_02062ea4(&obj1, &idx);
        func_020a8bb8(&obj2, &obj1);
        if (func_020707e8(&obj2, param + 0x4248, param[0xa6]) != 0) {
            func_0206fc80((u8) (i - 0x1323));
            func_0206fc4c(1);
            func_02070be8(&obj2);
            func_02062f4c(&obj1);
            return;
        }
        i++;
    }

    func_0206fc4c(0);
    func_02070be8(&obj2);
    func_02062f4c(&obj1);
}

void func_ov126_0229fa38(UnkStruct_0229fa38 *arg)
{
    char buf[0x70];
    int value;

    func_02070c08(buf);
    value = func_0206fc8c();
    func_02070934(buf, (const void *) data_ov126_022a2128, value);
    if (func_020707e8(buf, (void *) (&arg->unk_4248), arg->unk_A6) == 0) {
        func_0206fc4c(0);
    }
    func_02070be8(buf);
}

void func_ov126_0229f9b8(void *param)
{
    int x = func_020984e8();
    int y;
    int z;
    int i;

    func_02099870(x);
    y = func_02099870(x);
    z = func_0209871c((int) data_021dc7bc, y);

    for (i = 0; i < 4; i++) {
        if (i == z) {
            continue;
        }
        if (func_020988a4((int) data_021dc7bc, i) == 0) {
            continue;
        }
        if (func_02051bb4(func_020950a8(func_02099870(func_02098844((int) data_021dc7bc, i))), (char *) param + 0x4248, 6) ==
            0) {
            continue;
        }
        func_0206fc4c(2);
        return;
    }
    func_020950ac(func_02099870(x), (char *) param + 0x4248);
}

void func_ov126_0229f9a0(void *p)
{
    func_02064244((void *) data_021dc7aa, (char *) p + 0x4248);
}

void func_ov126_0229f968(UnkStruct_0229f968 *self)
{
    void *result = (void *) func_0206fc8c();
    if (func_020b1078(&self->unk_4248, result)) {
        func_0206fc4c(0);
    }
    func_020b141c(&self->unk_4248, result);
}

void func_ov126_0229f930(void *self)
{
    char buffer[20];
    void *handle;

    handle = func_02088220(data_021f3278);
    func_02051c08((void *) ((char *) self + 0x4248), (const void *) buffer, 10);
    func_02072e3c((unsigned int) ((void *) func_02072d4c((unsigned int) handle)), (unsigned char *) buffer);
}

void func_ov126_0229f90c(int *param)
{
    int *r4;
    int r0;
    int r1;
    int r2;

    r4 = param;

    r0 = func_02077c34((int) func_ov126_0229fc54());
    r1 = r0;
    r0 = (int) r4 + 0x4248;
    r2 = 6;
    func_02051c08((void *) r0, (const void *) r1, r2);
}

void func_ov126_0229f8e8(void *p)
{
    func_02051c08((char *) p + 0x4248, (void *) func_02077c38((char *) ((void *) func_ov126_0229fc54())), 6);
}

void func_ov126_0229f83c(int arg)
{
    unsigned int result = (unsigned int) func_0206fca4();

    if (result != 0xc && result != 0xd && result != 0xe) {
        func_ov126_0229f7dc(arg);
    }

    switch (result) {
        case 0xb:
            func_ov126_0229fb58((void *) arg);
            break;
        case 0xc:
            func_ov126_0229fb10((struct UnkStruct_0229fb10 *) arg);
            break;
        case 0xd:
            func_ov126_0229fa80((u8 *) arg);
            break;
        case 0xe:
            func_ov126_0229fa38((UnkStruct_0229fa38 *) arg);
            break;
        case 0xf:
            func_ov126_0229f9b8((void *) arg);
            break;
        case 0x10:
            func_ov126_0229f9a0((void *) arg);
            break;
        case 0x11:
            break;
        case 0x12:
            func_ov126_0229f968((UnkStruct_0229f968 *) arg);
            break;
        case 0x13:
            break;
        case 0x14:
            func_ov126_0229f930((void *) arg);
            break;
        case 0x15:
            break;
        case 0x16:
            break;
        case 0x17:
            break;
        case 0x18:
        case 0x19:
            func_ov126_0229f90c((int *) arg);
            break;
        case 0x1a:
        case 0x1b:
            func_ov126_0229f8e8((void *) arg);
            break;
        default:
            break;
    }
}
