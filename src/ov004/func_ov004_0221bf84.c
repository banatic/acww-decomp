/* func_ov004_0221bf84 @ 0x0221bf84, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202de4c(void *);
extern void func_020edb3c(void *);
extern char data_ov004_022535e4;

struct _Obj {
    void *vtbl;
};

void *func_ov004_0221bf84(struct _Obj *obj)
{
    obj->vtbl = &data_ov004_022535e4;
    func_0202de4c(obj);
    func_020edb3c(obj);
    return obj;
}
