/* func_02016174 @ 0x02016174, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066994(void *);
extern void func_020edb3c(void *);
extern char data_020d8bd4;

struct _Obj {
    void *vtbl;
};

void *func_02016174(struct _Obj *obj)
{
    obj->vtbl = &data_020d8bd4;
    func_02066994(obj);
    func_020edb3c(obj);
    return obj;
}
