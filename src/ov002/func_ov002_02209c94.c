/* func_ov002_02209c94 @ 0x02209c94, 0x20 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a39c(void *);
extern void func_020edb3c(void *);
extern char data_ov002_0220bc50;

struct _Obj {
    void *vtbl;
};

void *func_ov002_02209c94(struct _Obj *obj)
{
    obj->vtbl = &data_ov002_0220bc50;
    func_ov002_0220a39c(obj);
    func_020edb3c(obj);
    return obj;
}
