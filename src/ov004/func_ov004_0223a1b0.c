/* func_ov004_0223a1b0 @ 0x0223a1b0, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0223a4ec(void *);
extern void func_020edb3c(void *);
extern char data_ov004_02255e74;

struct _Obj {
    void *vtbl;
};

void *func_ov004_0223a1b0(struct _Obj *obj)
{
    obj->vtbl = &data_ov004_02255e74;
    func_ov004_0223a4ec(obj);
    func_020edb3c(obj);
    return obj;
}
