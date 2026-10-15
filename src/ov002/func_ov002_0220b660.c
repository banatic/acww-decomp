/* func_ov002_0220b660 @ 0x0220b660, 0x20 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208f46c(void *);
extern void func_020edb3c(void *);
extern char data_ov002_0220bd90;

struct _Obj {
    void *vtbl;
};

void *func_ov002_0220b660(struct _Obj *obj)
{
    obj->vtbl = &data_ov002_0220bd90;
    func_0208f46c(obj);
    func_020edb3c(obj);
    return obj;
}
