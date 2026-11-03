/* flea_market_villager_4: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221f860 @ 0x0221f860, 0x18 bytes, Thumb
 * func_ov004_0221f848 @ 0x0221f848, 0x18 bytes, Thumb
 * func_ov004_0221f828 @ 0x0221f828, 0x20 bytes, Thumb
 */

struct _Obj {
    void *vtbl;
};

extern void *func_0202decc(void *arg);
extern int data_ov004_02253b24;
extern void *func_0202de4c(void *);
extern void func_020edb3c(void *);

void *func_ov004_0221f860(void *arg)
{
    func_0202decc(arg);
    *(void **) arg = &data_ov004_02253b24;
    return arg;
}

void *func_ov004_0221f848(void *arg)
{
    *((void **) arg) = &data_ov004_02253b24;
    func_0202de4c(arg);
    return arg;
}

void *func_ov004_0221f828(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02253b24);
    func_0202de4c(obj);
    func_020edb3c(obj);
    return obj;
}
