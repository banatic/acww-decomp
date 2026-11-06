/* event_queue: 51 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203e444 @ 0x0203e444, 0x34 bytes, Thumb
 * func_0203e420 @ 0x0203e420, 0x22 bytes, Thumb
 * func_0203e3f8 @ 0x0203e3f8, 0x28 bytes, Thumb
 * func_0203e3c8 @ 0x0203e3c8, 0x2e bytes, Thumb
 * func_0203e37c @ 0x0203e37c, 0x4a bytes, Thumb
 * func_0203e370 @ 0x0203e370, 0xc bytes, Thumb
 * func_0203e364 @ 0x0203e364, 0xc bytes, Thumb
 * func_0203e358 @ 0x0203e358, 0xc bytes, Thumb
 * func_0203e34c @ 0x0203e34c, 0xc bytes, Thumb
 * func_0203e340 @ 0x0203e340, 0xc bytes, Thumb
 * func_0203e334 @ 0x0203e334, 0xc bytes, Thumb
 * func_0203e328 @ 0x0203e328, 0xc bytes, Thumb
 * func_0203e31c @ 0x0203e31c, 0xc bytes, Thumb
 * func_0203e310 @ 0x0203e310, 0xc bytes, Thumb
 * func_0203e304 @ 0x0203e304, 0xc bytes, Thumb
 * func_0203e2f8 @ 0x0203e2f8, 0xc bytes, Thumb
 * func_0203e2ec @ 0x0203e2ec, 0xc bytes, Thumb
 * func_0203e2e0 @ 0x0203e2e0, 0xc bytes, Thumb
 * func_0203e2c8 @ 0x0203e2c8, 0x18 bytes, Thumb
 * func_0203e2b8 @ 0x0203e2b8, 0x10 bytes, Thumb
 * func_0203e2a8 @ 0x0203e2a8, 0x10 bytes, Thumb
 * func_0203e280 @ 0x0203e280, 0x26 bytes, Thumb
 * func_0203e258 @ 0x0203e258, 0x28 bytes, Thumb
 * func_0203e234 @ 0x0203e234, 0x24 bytes, Thumb
 * func_0203e228 @ 0x0203e228, 0xc bytes, Thumb
 * func_0203e21c @ 0x0203e21c, 0xc bytes, Thumb
 * func_0203e210 @ 0x0203e210, 0xc bytes, Thumb
 * func_0203e204 @ 0x0203e204, 0xc bytes, Thumb
 * func_0203e1f8 @ 0x0203e1f8, 0xc bytes, Thumb
 * func_0203e1ec @ 0x0203e1ec, 0xc bytes, Thumb
 * func_0203e1c4 @ 0x0203e1c4, 0x28 bytes, Thumb
 * func_0203e19c @ 0x0203e19c, 0x28 bytes, Thumb
 * func_0203e190 @ 0x0203e190, 0xc bytes, Thumb
 * func_0203e168 @ 0x0203e168, 0x28 bytes, Thumb
 * func_0203e140 @ 0x0203e140, 0x28 bytes, Thumb
 * func_0203e110 @ 0x0203e110, 0x30 bytes, Thumb
 * func_0203e0e0 @ 0x0203e0e0, 0x30 bytes, Thumb
 * func_0203e0a8 @ 0x0203e0a8, 0x38 bytes, Thumb
 * func_0203e070 @ 0x0203e070, 0x38 bytes, Thumb
 * func_0203e020 @ 0x0203e020, 0x50 bytes, Thumb
 * func_0203dff0 @ 0x0203dff0, 0x2e bytes, Thumb
 * func_0203dfe4 @ 0x0203dfe4, 0xc bytes, Thumb
 * func_0203dfac @ 0x0203dfac, 0x38 bytes, Thumb
 * func_0203df94 @ 0x0203df94, 0x16 bytes, Thumb
 * func_0203df88 @ 0x0203df88, 0xc bytes, Thumb
 * func_0203df6c @ 0x0203df6c, 0x1c bytes, Thumb
 * func_0203df10 @ 0x0203df10, 0x5c bytes, Thumb
 * func_0203dee8 @ 0x0203dee8, 0x28 bytes, Thumb
 * func_0203dedc @ 0x0203dedc, 0xc bytes, Thumb
 * func_0203ded0 @ 0x0203ded0, 0xc bytes, Thumb
 * func_0203dec4 @ 0x0203dec4, 0xc bytes, Thumb
 */

struct UnkStruct_0203e258 {
    unsigned char pad_00[0x16];
    unsigned char unk_16;
};

typedef struct {
    char pad_00[0x10];
    int unk_10;
    char pad_14[2];
    unsigned char unk_16;
} UnkStruct_0203e020;

struct UnkStruct_0203df10 {
    char pad_00[0xc];
    int unk_0C;
    int unk_10;
    unsigned char unk_14;
    unsigned char unk_15;
    unsigned char unk_16;
};

struct UnkStruct_0203dee8 {
    char pad_00[0x16];
    char unk_16;
};

extern int func_020961a8(int);
extern int func_0203efbc(int);
extern int func_0203e478(int, int, int, int, int);
extern int func_0203e4c0(int);
extern unsigned int data_021c72c0;
extern unsigned char data_021c72b8[];
extern unsigned char data_021c72bc[];
extern int func_0203ef90(int);
extern void *func_020682e0(unsigned int heap_id);
extern void func_02068340(void *s, unsigned int val);
extern void func_02068320(int arg);
extern void func_0203f58c(void *arg);
extern int func_0203ec98(void);
extern void func_0206f5cc(void);
extern int func_02095f28(void);
extern int func_02095f08(int);
extern struct UnkStruct_0203df10 *func_0203f504(void);

int func_0203e31c(void);
int func_0203e2f8(void);
int func_0203e2c8(int x);
void func_0203e2b8(unsigned int arg);
void func_0203e2a8(unsigned int r0);

int func_0203e444(int a, int b)
{
    int x;
    if (b < 0) {
        return 0;
    }
    x = 0;
    if (a != 0) {
        x = func_0203efbc((int) ((void *) a));
    }
    return func_0203e478(x, 0, 3, 1, (unsigned char) ((unsigned char) b));
}

int func_0203e420(void)
{
    return func_0203e478(0, func_0203efbc(func_020961a8(4)), 8, 1, 0);
}

int func_0203e3f8(void)
{
    int result;
    unsigned char *ptr;

    if (func_0203e4c0(8) == 0) {
        return 0;
    }

    ptr = (*(unsigned char **) data_021c72b8);
    ptr[0x16] = 6;
    return 1;
}

int func_0203e3c8(int param)
{
    int temp;

    temp = func_020961a8(4);
    if (temp == 0) {
        return 0;
    }
    return func_0203e478(0, func_0203efbc(temp), 1, 2, param);
}

int func_0203e37c(void)
{
    int r4;

    if (func_0203e31c() != 0 || func_0203e2f8() != 0) {
        return 0;
    }
    r4 = func_020961a8(4);
    if (r4 == 0) {
        return 0;
    }
    func_0203e2a8(6);
    return func_0203e478(0, func_0203efbc(r4), 0xb, 1, 0);
}

int func_0203e370(void)
{
    return func_0203e2c8(2);
}

int func_0203e364(void)
{
    return func_0203e2c8(4);
}

void func_0203e358(void)
{
    func_0203e2b8(2);
}

void func_0203e34c(void)
{
    func_0203e2b8(4);
}

int func_0203e340(void)
{
    return func_0203e2c8(1);
}

void func_0203e334(void)
{
    func_0203e2b8(1);
}

void func_0203e328(void)
{
    func_0203e2a8(1);
}

int func_0203e31c(void)
{
    return func_0203e2c8(8);
}

void func_0203e310(void)
{
    func_0203e2b8(8);
}

void func_0203e304(void)
{
    func_0203e2a8(8);
}

int func_0203e2f8(void)
{
    return func_0203e2c8(0x20);
}

void func_0203e2ec(void)
{
    func_0203e2b8(0x20);
}

void func_0203e2e0(void)
{
    func_0203e2a8(0x20);
}

int func_0203e2c8(int x)
{
    if (((*(volatile int *) &data_021c72c0) & x) != 0) {
        return 1;
    } else {
        return 0;
    }
}

void func_0203e2b8(unsigned int arg)
{
    data_021c72c0 |= arg;
}

void func_0203e2a8(unsigned int r0)
{
    unsigned int r2;
    r2 = data_021c72c0;
    r2 &= ~r0;
    data_021c72c0 = r2;
}

int func_0203e280(int a)
{
    int x;

    x = func_0203efbc(func_020961a8(4));
    return func_0203e478(0, x, a, 4, 0);
}

int func_0203e258(unsigned char argument0)
{
    if (func_0203e4c0((unsigned char) ((unsigned char) argument0)) &&
        (*(struct UnkStruct_0203e258 **) data_021c72b8)->unk_16 != 6) {
        return 1;
    } else {
        return 0;
    }
}

int func_0203e234(unsigned char argument0)
{
    int result;
    unsigned char *ptr;

    if (func_0203e4c0((unsigned char) ((unsigned char) argument0)) == 0) {
        result = 0;
    } else {
        ptr = (*(unsigned char **) data_021c72b8);
        ptr[0x16] = 6;
        result = 1;
    }
    return result;
}

int func_0203e228(void)
{
    return func_0203e280(5);
}

int func_0203e21c(void)
{
    return func_0203e258(5);
}

void func_0203e210(void)
{
    func_0203e234(5);
}

int func_0203e204(void)
{
    return func_0203e280(10);
}

int func_0203e1f8(void)
{
    return func_0203e258(0xa);
}

int func_0203e1ec(void)
{
    return func_0203e234(10);
}

int func_0203e1c4(void)
{
    if ((*(int *) data_021c72b8) != 0) {
        return 0;
    }
    return func_0203e478(0, 0, 9, 0, 0);
}

int func_0203e19c(void)
{
    int ret;

    if (func_0203e4c0(9) == 0) {
        ret = 0;
    } else {
        (*(unsigned char **) data_021c72b8)[0x16] = 6;
        ret = 1;
    }
    return ret;
}

int func_0203e190(void)
{
    return func_0203e4c0(9);
}

int func_0203e168(void)
{
    if ((*(int *) data_021c72b8) != 0) {
        return 0;
    }
    return func_0203e478(0, 0, 14, 0, 0);
}

int func_0203e140(void)
{
    int result;
    unsigned char *ptr;

    if (func_0203e4c0(0xe) == 0) {
        result = 0;
    } else {
        ptr = (*(unsigned char **) data_021c72b8);
        ptr[0x16] = 6;
        result = 1;
    }
    return result;
}

int func_0203e110(void)
{
    int result;
    unsigned char *ptr;

    if (func_0203e4c0(4) == 0) {
        if (func_0203e4c0(12) == 0) {
            return 0;
        }
    }
    ptr = *(unsigned char **) data_021c72b8;
    ptr[0x17] = 6;
    return 1;
}

int func_0203e0e0(int a, int b)
{
    int result1 = 0;
    if (b != 0) {
        result1 = func_0203efbc(b);
    }
    return func_0203e478(func_0203efbc(a), result1, 2, 3, 0);
}

int func_0203e0a8(int arg0, int arg1)
{
    int tmp1;
    int tmp2;
    if (arg1 == 0) {
        tmp1 = func_0203efbc(func_020961a8(4));
        tmp2 = func_0203efbc(arg0);
        return func_0203e478(tmp1, tmp2, 6, 3, 0);
    } else {
        return 0;
    }
}

int func_0203e070(int a, int b)
{
    int x;
    int y;

    if (b == 0) {
        x = func_0203efbc(func_020961a8(4));
        y = func_0203efbc(a);
        return func_0203e478(x, y, 7, 3, 0);
    }
    return 0;
}

int func_0203e020(int param)
{
    UnkStruct_0203e020 *p;
    if (func_0203e4c0(2) != 0) {
        goto outer_success;
    }
    if (func_0203e4c0(6) != 0) {
        goto outer_success;
    }
    if (func_0203e4c0(7) != 0) {
        goto outer_success;
    }
    return 0;

outer_success:
    p = (*(UnkStruct_0203e020 **) data_021c72b8);
    if (p->unk_10 == func_0203efbc(param)) {
        goto inner_success;
    }
    return 0;

inner_success:
    p->unk_16 = 6;
    return 1;
}

int func_0203dff0(void)
{
    return func_0203e4c0(2) || func_0203e4c0(6) || func_0203e4c0(7);
}

void func_0203dfe4(unsigned int r0)
{
    unsigned int *r1 = (unsigned int *) data_021c72bc;
    *r1 = r0;
}

int func_0203dfac(void)
{
    if (func_0203e4c0(2) != 0 || func_0203e4c0(6) != 0 || func_0203e4c0(7) != 0) {
        return func_0203ef90((*(int *) data_021c72bc));
    } else {
        return 0;
    }
}

void func_0203df94(unsigned int receiver)
{
    func_02068340(func_020682e0(0), receiver);
}

void func_0203df88(void *self)
{
    func_02068320(*(int *) ((char *) self + 0x40));
}

void func_0203df6c(void)
{
    func_0203f58c((*(void **) data_021c72b8));
    (*(void **) data_021c72b8) = 0;
}

int func_0203df10(void)
{
    struct UnkStruct_0203df10 *p;
    if (func_020961a8(4) == 0) {
        return 0;
    }
    if (func_0203ec98() != 0) {
        func_0206f5cc();
        return 0;
    }
    if (func_02095f28() == 0) {
        return 0;
    }

    func_02095f08(1);
    p = func_0203f504();
    p->unk_0C = 0;
    p->unk_10 = 0;
    p->unk_15 = 0xd;
    p->unk_14 = 3;
    p->unk_16 = 5;
    (*(struct UnkStruct_0203df10 **) data_021c72b8) = p;
    return 1;
}

int func_0203dee8(void)
{
    if (func_0203e4c0(13) != 0) {
        (*(struct UnkStruct_0203dee8 **) data_021c72b8)->unk_16 = 6;
        return 1;
    } else {
        return 0;
    }
}

int func_0203dedc(void)
{
    return func_0203e2c8(0x10);
}

void func_0203ded0(void)
{
    func_0203e2b8(0x10);
}

void func_0203dec4(void)
{
    func_0203e2a8(0x10);
}
