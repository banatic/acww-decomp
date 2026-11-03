/* missing_npc2_2: 21 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020c365c @ 0x020c365c, 0x34 bytes, Thumb
 * func_020c3640 @ 0x020c3640, 0x1c bytes, Thumb
 * func_020c363c @ 0x020c363c, 0x4 bytes, Thumb
 * func_020c3610 @ 0x020c3610, 0x2c bytes, Thumb
 * func_020c35d8 @ 0x020c35d8, 0x38 bytes, Thumb
 * func_020c35d4 @ 0x020c35d4, 0x4 bytes, Thumb
 * func_020c35d0 @ 0x020c35d0, 0x4 bytes, Thumb
 * func_020c35cc @ 0x020c35cc, 0x4 bytes, Thumb
 * func_020c35c0 @ 0x020c35c0, 0xc bytes, Thumb
 * func_020c3580 @ 0x020c3580, 0x40 bytes, Thumb
 * func_020c3578 @ 0x020c3578, 0x8 bytes, Thumb
 * func_020c3574 @ 0x020c3574, 0x4 bytes, Thumb
 * func_020c3534 @ 0x020c3534, 0x40 bytes, Thumb
 * func_020c34e4 @ 0x020c34e4, 0x50 bytes, Thumb
 * func_020c349c @ 0x020c349c, 0x48 bytes, Thumb
 * func_020c344c @ 0x020c344c, 0x50 bytes, Thumb
 * func_020c340c @ 0x020c340c, 0x40 bytes, Thumb
 * func_020c33bc @ 0x020c33bc, 0x50 bytes, Thumb
 * func_020c33a4 @ 0x020c33a4, 0x18 bytes, Thumb
 * func_020c338c @ 0x020c338c, 0x18 bytes, Thumb
 * func_020c336c @ 0x020c336c, 0x20 bytes, Thumb
 */

struct UnkStruct_020c34e4 {
    char pad_00[0x564];
    char unk_564;
};

typedef struct UnkStruct_020c33bc {
    char pad_00[0x564];
    int member;
} UnkStruct_020c33bc;

extern unsigned short data_020c80f8;
extern int func_020b65c4(void);
extern void func_020c3690(int param1, int param2);
extern int func_02014868(int);
extern int func_0203e020(int);
extern int func_02016104(void *p);
extern int func_0201c314(void *p, int x);
extern int func_020147fc(void *p, int a, int b, int c);
extern void func_0201ad18(void *a, int b, int c, int d, void *e, int f, void *g, int h);
extern int *data_020c814c;
extern unsigned char data_021fbee8[];
extern int func_02019d0c(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);
extern int func_02019de8(void *ptr);
extern int func_02019e00(void *ptr);
extern void func_0201af1c(int, int);
extern void *func_0202eb70(void *obj);
extern unsigned char data_020e7e14[];
extern void *func_0202eb20(void *);
extern void func_020edb3c(void *);

int func_020c365c(char *param)
{
    func_02019d0c((int) (param + 0x564), 0, 1, 0, 0, 0, 0, 0, 0, (unsigned short) data_020c80f8, 0);
    return 1;
}

int func_020c3640(int param1)
{
    int r4;
    int result;

    r4 = param1;
    result = func_020b65c4();
    if (result == 0) {
        func_020c3690(r4, 7);
    }
    return 1;
}

int func_020c363c(void)
{
    return 1;
}

int func_020c3610(int arg0)
{
    int r4;
    int result;

    r4 = arg0;
    if (func_02014868(r4 + 0x618) == 0) {
        func_0203e020(r4);
        func_020c3690(r4, 2);
    }
    return 1;
}

int func_020c35d8(void *self)
{
    int r1 = func_02016104((char *) self + 0x658);
    int r2 = 0;
    if (r1 != 0) {
        r2 = func_0201c314(self, r1);
    }
    func_020147fc((char *) self + 0x618, 0, r2, 0);
    return 1;
}

int func_020c35d4(void)
{
    return 1;
}

int func_020c35d0(void)
{
    return 1;
}

int func_020c35cc(void)
{
    return 1;
}

void func_020c35c0(int a)
{
    func_020c3690(a, 3);
}

void func_020c3580(char *p)
{
    func_0201ad18(p + 0x3b0, 1, 0, 0, (void *) data_021fbee8, 4, data_020c814c, 1);
    func_020c3690((int) p, 0);
}

void func_020c3578(char *argument0)
{
    func_020c365c((char *) argument0);
}

int func_020c3574(void)
{
    return 1;
}

int func_020c3534(int param)
{
    func_02019d0c(param + 0x564, 2, 2, 0xf400, 0x14600, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_020c34e4(struct UnkStruct_020c34e4 *self)
{
    if (func_02019de8(&self->unk_564) == 0) {
        goto done;
    }
    if (func_02019e00(&self->unk_564) != 2) {
        goto done;
    }
    func_02019d0c((int) (&self->unk_564), 0, 2, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
done:
    return 1;
}

int func_020c349c(char *p)
{
    func_02019d0c((int) p + 0x564, 3, 2, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    func_0201af1c((int) p + 0x350, 2);
    return 1;
}

int func_020c344c(void *p)
{
    if (func_02019de8((char *) p + 0x564) != 0) {
        if (func_02019e00((char *) p + 0x564) == 3) {
            func_02019d0c((int) ((char *) p + 0x564), 0, 2, 0, 0, 0, 0, 0, 0, (unsigned short) data_020c80f8, 0);
        }
    }
    return 1;
}

int func_020c340c(char *param)
{
    func_02019d0c((int) (param + 0x564), 4, 2, 0x10000, 0x1d000, 0, 0, 0, 0, (unsigned short) data_020c80f8, 0);
    return 1;
}

int func_020c33bc(UnkStruct_020c33bc *param)
{
    if (func_02019de8(&param->member) != 0 && func_02019e00(&param->member) == 1) {
        func_02019d0c((int) (&param->member), 0, 2, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    }
    return 1;
}

void *func_020c33a4(void *obj)
{
    func_0202eb70(obj);
    *(void **) obj = data_020e7e14;
    return obj;
}

void *func_020c338c(void *this)
{
    *(void **) this = ((char *) data_020e7e14);
    func_0202eb20(this);
    return this;
}

void *func_020c336c(void *self)
{
    *(void **) self = (void *) data_020e7e14;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
