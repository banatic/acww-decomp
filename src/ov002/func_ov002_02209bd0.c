/* func_ov002_02209bd0 @ 0x02209bd0, 0x20 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070ba4(void *);
extern void func_020edb3c(void *);
extern char data_ov002_0220bba8;

struct _Obj {
    void *vtbl;
};

void *func_ov002_02209bd0(struct _Obj *obj)
{
    obj->vtbl = &data_ov002_0220bba8;
    func_02070ba4(obj);
    func_020edb3c(obj);
    return obj;
}
