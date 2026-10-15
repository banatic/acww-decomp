/* func_ov002_0220b444 @ 0x0220b444, 0x20 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_0220b648(void *);
extern void func_020edb3c(void *);
extern char data_ov002_0220bd74;

struct _Obj {
    void *vtbl;
};

void *func_ov002_0220b444(struct _Obj *obj)
{
    obj->vtbl = &data_ov002_0220bd74;
    func_ov002_0220b648(obj);
    func_020edb3c(obj);
    return obj;
}
