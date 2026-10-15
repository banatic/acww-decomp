/* func_ov004_022451c4 @ 0x022451c4, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_02245474(void *);
extern void func_020edf54(void *);
extern char data_ov004_022566d8;

struct _Obj {
    void *vtbl;
};

void *func_ov004_022451c4(struct _Obj *obj)
{
    obj->vtbl = &data_ov004_022566d8;
    func_ov004_02245474(obj);
    func_020edf54(obj);
    return obj;
}
