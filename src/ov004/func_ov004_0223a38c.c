/* func_ov004_0223a38c @ 0x0223a38c, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_0223a4ec(void *);
extern void func_020edb3c(void *);
extern char data_ov004_02255ea4;

struct _Obj {
    void *vtbl;
};

void *func_ov004_0223a38c(struct _Obj *obj)
{
    obj->vtbl = &data_ov004_02255ea4;
    func_ov004_0223a4ec(obj);
    func_020edb3c(obj);
    return obj;
}
