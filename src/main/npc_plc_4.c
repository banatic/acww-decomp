/* npc_plc_4: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020c3d78 @ 0x020c3d78, 0x34 bytes, Thumb
 * func_020c3d74 @ 0x020c3d74, 0x4 bytes, Thumb
 * func_020c3d30 @ 0x020c3d30, 0x44 bytes, Thumb
 * func_020c3d04 @ 0x020c3d04, 0x2c bytes, Thumb
 * func_020c3d00 @ 0x020c3d00, 0x4 bytes, Thumb
 * func_020c3cc4 @ 0x020c3cc4, 0x3c bytes, Thumb
 * func_020c3c94 @ 0x020c3c94, 0x30 bytes, Thumb
 * func_020c3c7c @ 0x020c3c7c, 0x18 bytes, Thumb
 * func_020c3c64 @ 0x020c3c64, 0x18 bytes, Thumb
 * func_020c3c44 @ 0x020c3c44, 0x20 bytes, Thumb
 */

struct Object {
    void *unk_00;
};

extern unsigned short data_020c80f8;
extern int func_02019d0c(int, int, int, int, int, int, int, int, int, int, int);
extern int func_02016104(void *p);
extern int func_0201c314(void *self, int flag);
extern int func_020147fc(void *p1, int a, int b, int c);
extern void func_020c3c18(void *p, int a);
extern int func_02014868(void *ptr);
extern int func_0203e020(void *ptr);
extern void func_020c3dac(void *ptr, int arg);
extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern void *func_020161ac(void *);
extern void *func_0201615c(void *);
extern char data_020e86ec;
extern void func_020edb3c(struct Object *obj);

int func_020c3d78(int a)
{
    func_02019d0c(a + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_020c3d74(void)
{
    return 1;
}

int func_020c3d30(char *self)
{
    int r1 = func_02016104(self + 0x658);
    int r2 = 0;

    if (r1 != 0) {
        r2 = func_0201c314(self, r1);
    }
    func_020147fc(self + 0x618, 0, r2, 0);
    func_020c3c18(self + 0x658, 0);
    return 1;
}

int func_020c3d04(void *ptr)
{
    if (func_02014868((char *) ptr + 0x618) == 0) {
        func_0203e020(ptr);
        func_020c3dac(ptr, 2);
    }
    return 1;
}

int func_020c3d00(void)
{
    return 1;
}

int func_020c3cc4(void *self)
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

    func_02019d0c((int) ((char *) self + 0x564), 3, 1, 0, arg5, arg6, arg7, arg8, arg9, arg10, arg11);
    return 1;
}

int func_020c3c94(void *param)
{
    if (func_02019e00((char *) param + 0x564) == 3) {
        if (func_02019de8((char *) param + 0x564) == 1) {
            func_020c3dac(param, 0);
        }
    }
    return 1;
}

void *func_020c3c7c(void *obj)
{
    func_020161ac(obj);
    *(void **) obj = ((unsigned char *) &data_020e86ec);
    return obj;
}

void *func_020c3c64(void *arg)
{
    *(void **) arg = (void *) &data_020e86ec;
    func_0201615c(arg);
    return arg;
}

struct Object *func_020c3c44(struct Object *obj)
{
    obj->unk_00 = &data_020e86ec;
    func_0201615c((void *) obj);
    func_020edb3c(obj);
    return obj;
}
