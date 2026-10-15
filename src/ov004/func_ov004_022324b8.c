/* func_ov004_022324b8 @ 0x022324b8, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02056578(void *);
extern void func_020edb3c(void *);
extern char data_ov004_02255ab8;

struct _Obj {
    void *vtbl;
};

void *func_ov004_022324b8(struct _Obj *obj)
{
    obj->vtbl = &data_ov004_02255ab8;
    func_02056578(obj);
    func_020edb3c(obj);
    return obj;
}
