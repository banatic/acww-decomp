/* func_ov004_0222f408 @ 0x0222f408, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_0222c7a0(void *);
extern void func_020edf54(void *);
extern char data_ov004_02255290;

struct _Obj {
    void *vtbl;
};

void *func_ov004_0222f408(struct _Obj *obj)
{
    obj->vtbl = &data_ov004_02255290;
    func_ov004_0222c7a0(obj);
    func_020edf54(obj);
    return obj;
}
