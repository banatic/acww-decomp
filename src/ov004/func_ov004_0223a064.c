/* func_ov004_0223a064 @ 0x0223a064, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0223a374(void *);
extern void func_020edb3c(void *);
extern char data_ov004_02255de4;

struct _Obj {
    void *vtbl;
};

void *func_ov004_0223a064(struct _Obj *obj)
{
    obj->vtbl = &data_ov004_02255de4;
    func_ov004_0223a374(obj);
    func_020edb3c(obj);
    return obj;
}
