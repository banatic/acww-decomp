/* func_02068b64 @ 0x02068b64, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02068b88(void *arg1, void *arg2);

typedef void *(*FuncType)(void *);

void func_02068b64(void *p)
{
    void *base;
    void *obj;
    void *vtable;
    FuncType fn;
    void *ret;

    base = *(void **) ((char *) p + 4);
    obj = *(void **) ((char *) base + 0x14a8);
    vtable = *(void **) obj;
    fn = *(FuncType *) ((char *) vtable + 0x6c);
    ret = fn(obj);
    func_02068b88(p, ret);
}
