/* shop_display_5: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022468e8 @ 0x022468e8, 0x18 bytes, Thumb
 * func_ov004_022468b0 @ 0x022468b0, 0x38 bytes, Thumb
 * func_ov004_02246848 @ 0x02246848, 0x68 bytes, Thumb
 * func_ov004_02246828 @ 0x02246828, 0x20 bytes, Thumb
 * func_ov004_02246808 @ 0x02246808, 0x20 bytes, Thumb
 * func_ov004_022467e0 @ 0x022467e0, 0x28 bytes, Thumb
 */

typedef struct {
    unsigned short id;
    unsigned short unk_02;
} UnkStruct_02246848;

extern int func_020edf70(int);
extern int func_020b6730(void);
extern int func_020b6760(void);
extern int func_020b65c4(void);
extern char data_ov004_0224c664[];
extern char data_ov004_0224be64[];
extern char data_ov004_0224c264[];
extern void func_02061e2c(UnkStruct_02246848 *out, int a);
extern int func_0204bcdc(UnkStruct_02246848 *a);
extern int func_0204c4e8(UnkStruct_02246848 *a);
extern int func_0204c520(UnkStruct_02246848 *a);
extern void *func_020ee660(void *);
extern void func_020ee62c(void *ptr);
extern void *const data_ov004_022568c4[];
extern void *const data_020da13c[];
extern void func_020edf54(void *p);

void *func_ov004_02246828(void *self);

void func_ov004_022468e8(void)
{
    int result;

    result = func_020edf70(0x58);
    if (result == 0) {
        return;
    }
    func_ov004_02246828((void *) result);
}

char *func_ov004_022468b0(void)
{
    if (func_020b6730() != 0) {
        return data_ov004_0224c664 + (func_020b6760() << 10);
    }
    if (func_020b65c4() == 0xa) {
        return data_ov004_0224be64;
    }
    return data_ov004_0224c264;
}

int func_ov004_02246848(int a)
{
    UnkStruct_02246848 t;
    unsigned short v;
    int f;

    func_02061e2c(&t, a);
    if (func_0204bcdc(&t) != 0) {
        return 0x19;
    }
    if (func_0204c4e8(&t) != 0) {
        goto r42;
    }
    f = 0;
    v = t.id;
    if (v >= 0x156c && v <= 0x156c) {
        f = 1;
    }
    if (f != 0) {
    r42:
        return 0x42;
    }
    if (v >= 0x13a8 && v <= 0x13c7) {
        return 9;
    }
    return func_0204c520(&t);
}

void *func_ov004_02246828(void *self)
{
    func_020ee660(self);
    *(void **) self = (void *) ((int *) data_020da13c);
    *(void **) self = (void *) ((int *) data_ov004_022568c4);
    return self;
}

void *func_ov004_02246808(void *p)
{
    volatile int *vp;
    vp = (volatile int *) p;
    *vp = (int) ((int *) data_ov004_022568c4);
    *vp = (int) ((int *) data_020da13c);
    func_020ee62c(p);
    return p;
}

void *func_ov004_022467e0(const void **self)
{
    *self = data_ov004_022568c4;
    *self = data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}
