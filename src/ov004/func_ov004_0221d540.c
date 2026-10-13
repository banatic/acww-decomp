/* func_ov004_0221d540 @ 0x0221d540, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202de4c(void *);
extern void func_020edb3c(void *);
extern char data_ov004_022537d8;

struct _Obj {
    void *vtbl;
};

void *func_ov004_0221d540(struct _Obj *obj)
{
    obj->vtbl = &data_ov004_022537d8;
    func_0202de4c(obj);
    func_020edb3c(obj);
    return obj;
}
