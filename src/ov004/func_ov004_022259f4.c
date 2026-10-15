/* func_ov004_022259f4 @ 0x022259f4, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202ee5c(void *);
extern void func_020edf54(void *);
extern char data_ov004_02254a38;

struct _Obj {
    void *vtbl;
};

void *func_ov004_022259f4(struct _Obj *obj)
{
    obj->vtbl = &data_ov004_02254a38;
    func_0202ee5c(obj);
    func_020edf54(obj);
    return obj;
}
