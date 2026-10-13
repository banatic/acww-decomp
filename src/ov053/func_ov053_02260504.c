/* func_ov053_02260504 @ 0x02260504, 0x54 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b, c;
} Tri;

extern int func_ov053_02260474(void *);
extern Tri *func_02095794(int);
extern void func_ov053_02260bb0(void *, int);
extern void func_0203e0a8(void *, int);
extern Tri data_ov053_022617c8;

int func_ov053_02260504(void *arg)
{
    volatile Tri t;
    Tri *p;

    if (func_ov053_02260474(arg) == 0) {
        return 0;
    }
    p = func_02095794(4);
    t.a = p->a;
    t.b = p->b;
    t.c = p->c;
    if (p->c > data_ov053_022617c8.c) {
        func_ov053_02260bb0((char *) arg + 0x658, 8);
        func_0203e0a8(arg, 0);
        return 1;
    }
    return 0;
}
