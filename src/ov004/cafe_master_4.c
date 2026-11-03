/* cafe_master_4: 7 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02224610 @ 0x02224610, 0x38 bytes, Thumb
 * func_ov004_022245b8 @ 0x022245b8, 0x58 bytes, Thumb
 * func_ov004_022245b4 @ 0x022245b4, 0x4 bytes, Thumb
 * func_ov004_022245b0 @ 0x022245b0, 0x4 bytes, Thumb
 * func_ov004_02224598 @ 0x02224598, 0x18 bytes, Thumb
 * func_ov004_02224580 @ 0x02224580, 0x18 bytes, Thumb
 * func_ov004_02224560 @ 0x02224560, 0x20 bytes, Thumb
 */

struct UnkStruct_022245b8 {
    char pad_00[0x64];
    int unk_64;
};

struct _Obj {
    void *vtbl;
};

extern void func_0201ad18(int, int, int, int, int, int, int, int);
extern unsigned char data_020c814c[];
extern unsigned char data_021fbee8[];
extern int func_0201c0e0(int);
extern int func_0201c040(int, int *, int *);
extern int func_020a7278(void);
extern void func_0201c054(int, int, int, int);
extern void func_ov004_022249b4(int, int);
extern struct UnkStruct_022245b8 *data_020ccf94;
extern void *func_020161ac(void *arg);
extern int data_ov004_02254650;
extern void *func_0201615c(void *);
extern void func_020edb3c(void *);

int func_ov004_02224610(int a)
{
    func_0201ad18(a + 0x3b0, 0, 0, 0, (unsigned int) data_021fbee8, 4, *((int *) data_020c814c), 1);
    return 1;
}

int func_ov004_022245b8(int arg)
{
    int a, b;
    if (func_0201c0e0(arg) != 0) {
        a = 4;
        b = 4;
        if (func_0201c040(arg, &a, &b) != 0) {
            if (a == 4) {
                if (func_020a7278() != 0) {
                    func_0201c054(arg, 1, data_020ccf94->unk_64, 4);
                    func_ov004_022249b4(arg, 0);
                }
            }
        }
    }
    return 1;
}

int func_ov004_022245b4(void)
{
    return 1;
}

int func_ov004_022245b0(void)
{
    return 1;
}

void *func_ov004_02224598(void *arg)
{
    func_020161ac(arg);
    *(void **) arg = &data_ov004_02254650;
    return arg;
}

void *func_ov004_02224580(void *arg)
{
    *((void **) arg) = &data_ov004_02254650;
    func_0201615c(arg);
    return arg;
}

void *func_ov004_02224560(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02254650);
    func_0201615c(obj);
    func_020edb3c(obj);
    return obj;
}
