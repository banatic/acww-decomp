/* museum_room_setup: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02245214 @ 0x02245214, 0x18 bytes, Thumb
 * func_ov004_022451fc @ 0x022451fc, 0x18 bytes, Thumb
 * func_ov004_022451e4 @ 0x022451e4, 0x18 bytes, Thumb
 * func_ov004_022451c4 @ 0x022451c4, 0x20 bytes, Thumb
 * func_ov004_022451c0 @ 0x022451c0, 0x4 bytes, Thumb
 */

struct _Obj {
    void *vtbl;
};

extern int func_020edf70(int);
extern void *func_ov004_022454fc(void *arg);
extern int data_ov004_022566d8;
extern void *func_ov004_02245474(void *);
extern void func_020edf54(void *);

void *func_ov004_022451fc(void *arg);

void func_ov004_02245214(void)
{
    int result;

    result = func_020edf70(0x50);
    if (result == 0) {
        return;
    }
    func_ov004_022451fc((void *) result);
}

void *func_ov004_022451fc(void *arg)
{
    func_ov004_022454fc(arg);
    *(void **) arg = &data_ov004_022566d8;
    return arg;
}

void *func_ov004_022451e4(void *arg)
{
    *((void **) arg) = &data_ov004_022566d8;
    func_ov004_02245474(arg);
    return arg;
}

void *func_ov004_022451c4(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_022566d8);
    func_ov004_02245474(obj);
    func_020edf54(obj);
    return obj;
}

int func_ov004_022451c0(void)
{
    return 1;
}
