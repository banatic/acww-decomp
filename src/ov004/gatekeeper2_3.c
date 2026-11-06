/* gatekeeper2_3: 17 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022256c8 @ 0x022256c8, 0x24 bytes, Thumb
 * func_ov004_022256c4 @ 0x022256c4, 0x4 bytes, Thumb
 * func_ov004_02225670 @ 0x02225670, 0x54 bytes, Thumb
 * func_ov004_02225634 @ 0x02225634, 0x3c bytes, Thumb
 * func_ov004_02225630 @ 0x02225630, 0x4 bytes, Thumb
 * func_ov004_0222562c @ 0x0222562c, 0x4 bytes, Thumb
 * func_ov004_022255f0 @ 0x022255f0, 0x3c bytes, Thumb
 * func_ov004_022255c0 @ 0x022255c0, 0x30 bytes, Thumb
 * func_ov004_022255bc @ 0x022255bc, 0x4 bytes, Thumb
 * func_ov004_02225540 @ 0x02225540, 0x7c bytes, Thumb
 * func_ov004_0222553c @ 0x0222553c, 0x4 bytes, Thumb
 * func_ov004_022254e4 @ 0x022254e4, 0x58 bytes, Thumb
 * func_ov004_022254e0 @ 0x022254e0, 0x4 bytes, Thumb
 * func_ov004_022254dc @ 0x022254dc, 0x4 bytes, Thumb
 * func_ov004_022254c4 @ 0x022254c4, 0x18 bytes, Thumb
 * func_ov004_022254ac @ 0x022254ac, 0x18 bytes, Thumb
 * func_ov004_0222548c @ 0x0222548c, 0x20 bytes, Thumb
 */

typedef void (*VF)(void *);

struct UnkStruct_022254e4 {
    char pad_00[0x64];
    int unk_64;
};

struct _Obj {
    void *vtbl;
};

extern int func_02019c6c(int a, int b, unsigned short c);
extern unsigned short data_020c80f8;
extern int func_0201c2a4(void *self, int a);
extern void func_02016108(void *p, int n);
extern int func_02016104(void *p);
extern int func_0201c314(void *self, int n);
extern int func_020147fc(void *p, int a, int b, int c);
extern int func_02014868(void *p);
extern int func_0203e020(void *self);
extern void func_ov004_022256ec(void *self, int k);
extern int func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern int func_0201c0e0(void *self);
extern int func_0201c040(void *self, int *a, int *b);
extern char *data_020ccf94;
extern void func_0201c054(void *self, int a, int b, int c);
extern int func_020a7278(void);
extern void *func_020161ac(void *arg);
extern int data_ov004_02254888;
extern void *func_0201615c(void *);
extern void func_020edb3c(void *);

int func_ov004_022256c8(int a)
{
    func_02019c6c(a + 0x564, 1, data_020c80f8);
    return 1;
}

int func_ov004_022256c4(void)
{
    return 1;
}

int func_ov004_02225670(char *self)
{
    int n;
    int r;

    (*(VF **) (self + 0x658))[2](self + 0x658);
    func_02016108(self + 0x658, func_0201c2a4(self, 4));
    n = func_02016104(self + 0x658);
    r = 0;
    if (n != 0) {
        r = func_0201c314(self, n);
    }
    func_020147fc(self + 0x618, 0, r, 0);
    return 1;
}

int func_ov004_02225634(unsigned char *self)
{
    if (func_02014868(self + 0x618) != 0) {
        return 1;
    }
    if (func_02014868(self + 0x618) == 0) {
        func_0203e020(self);
        func_ov004_022256ec(self, 2);
    }
    return 1;
}

int func_ov004_02225630(void)
{
    return 1;
}

int func_ov004_0222562c(void)
{
    return 1;
}

int func_ov004_022255f0(void *self)
{
    int arg5;
    int arg6;
    int arg7;
    int arg8;
    int arg9;
    int arg10;
    int arg11;

    arg5 = 0;
    arg6 = 0;
    arg7 = *(signed short *) ((char *) self + 0x710);
    arg8 = 0;
    arg9 = 0;
    arg10 = data_020c80f8;
    arg11 = 0;

    func_02019d0c((char *) self + 0x564, 3, 1, 0, arg5, arg6, arg7, arg8, arg9, arg10, arg11);
    return 1;
}

int func_ov004_022255c0(void *self)
{
    if (func_02019e00((char *) self + 0x564) == 3) {
        if (func_02019de8((char *) self + 0x564) != 0) {
            func_ov004_022256ec(self, 0);
        }
    }
    return 1;
}

int func_ov004_022255bc(void)
{
    return 1;
}

int func_ov004_02225540(char *self)
{
    int a, b;

    if (func_0201c0e0(self) != 0) {
        a = 4;
        b = 4;
        if (func_0201c040(self, &a, &b) != 0 && a == *(int *) (data_020ccf94 + 0x64) && a == b) {
            func_0201c054(self, 1, *(int *) (data_020ccf94 + 0x64), *(int *) (data_020ccf94 + 0x64));
            func_ov004_022256ec(self, 1);
        } else if (func_020a7278() != 0 && b == 4) {
            func_0201c054(self, 1, *(int *) (data_020ccf94 + 0x64), 4);
            func_ov004_022256ec(self, 0);
        }
    }
    return 1;
}

int func_ov004_0222553c(void)
{
    return 1;
}

int func_ov004_022254e4(int arg)
{
    int a, b;
    if (func_0201c0e0((void *) arg) != 0) {
        a = 4;
        b = 4;
        if (func_0201c040((void *) arg, &a, &b) != 0) {
            if (a == 4) {
                if (func_020a7278() != 0) {
                    func_0201c054((void *) arg, 1, (*(struct UnkStruct_022254e4 **) &data_020ccf94)->unk_64, 4);
                    func_ov004_022256ec((void *) arg, 3);
                }
            }
        }
    }
    return 1;
}

int func_ov004_022254e0(void)
{
    return 1;
}

int func_ov004_022254dc(void)
{
    return 1;
}

void *func_ov004_022254c4(void *arg)
{
    func_020161ac(arg);
    *(void **) arg = &data_ov004_02254888;
    return arg;
}

void *func_ov004_022254ac(void *arg)
{
    *((void **) arg) = &data_ov004_02254888;
    func_0201615c(arg);
    return arg;
}

void *func_ov004_0222548c(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02254888);
    func_0201615c(obj);
    func_020edb3c(obj);
    return obj;
}
