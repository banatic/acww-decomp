/* func_02048d2c @ 0x02048d2c, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Pair {
    int a;
    int b;
} Pair;
extern int func_020644cc(int);
extern void *data_020ccf94;
extern int func_02073d90(void *);
extern int func_020b65c4(void);
extern void func_0204f538(void *, unsigned short *, int, int, int);
extern void func_0204f380(void *, int, int);
extern void func_0204f31c(void *, int, int);
extern void func_0205f9d4(int, int, int, unsigned short, int);
inline Pair *inline_fn(Pair *arg0)
{
    return arg0;
}

int func_02048d2c(void *a0, void *obj, int count, Pair *arr, unsigned short arg5, int arg6)
{
    int ret = -1;
    Pair *ptr;
    Pair *p = arr;
    if (count > 0) {
        ret = func_020644cc(count);
        p = inline_fn(p + ret);
        if (func_02073d90(data_020ccf94) != 0) {
            goto update;
        }
        {
            unsigned short tmp = arg5;
            ptr = p;
            func_0204f538(obj, &tmp, p->a, p->b, 0);
            if (arg6 != 0) {
                func_0204f380(obj, p->a, ptr->b);
            } else {
                func_0204f31c(obj, p->a, p->b);
            }
        }
        goto end;
    update: {
        int v = func_020b65c4();
        func_0205f9d4((signed char) p->a, (signed char) p->b, v, arg5, arg6);
    }

    end:;
    }
    return ret;
}
