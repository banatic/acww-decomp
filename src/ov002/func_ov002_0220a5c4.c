/* func_ov002_0220a5c4 @ 0x0220a5c4, 0x20 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208ebb8(void *);
extern void func_020edb3c(void *);
extern char data_ov002_0220bcec;

struct _Obj {
    void *vtbl;
};

void *func_ov002_0220a5c4(struct _Obj *obj)
{
    obj->vtbl = &data_ov002_0220bcec;
    func_0208ebb8(obj);
    func_020edb3c(obj);
    return obj;
}
