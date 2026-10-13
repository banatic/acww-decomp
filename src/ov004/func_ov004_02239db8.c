/* func_ov004_02239db8 @ 0x02239db8, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0223a4ec(void *);
extern void func_020edb3c(void *);
extern char data_ov004_02255e2c;

struct _Obj {
    void *vtbl;
};

void *func_ov004_02239db8(struct _Obj *obj)
{
    obj->vtbl = &data_ov004_02255e2c;
    func_ov004_0223a4ec(obj);
    func_020edb3c(obj);
    return obj;
}
