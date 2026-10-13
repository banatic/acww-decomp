/* func_ov004_02221974 @ 0x02221974, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202de4c(void *);
extern void func_020edb3c(void *);
extern char data_ov004_02253f44;

struct _Obj {
    void *vtbl;
};

void *func_ov004_02221974(struct _Obj *obj)
{
    obj->vtbl = &data_ov004_02253f44;
    func_0202de4c(obj);
    func_020edb3c(obj);
    return obj;
}
