/* func_ov139_02299b54 @ 0x02299b54, 0x3c bytes, Thumb, module ov139
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_0220b10c(void *p);
extern void __cxa_vec_ctor(void *data, int a, int b, void (*callback3)(void *), void (*callback4)(void *));
extern void *func_020b9cfc(void *p);
extern int **func_02070be8(void *element);
extern void *func_02070c08(void *element);

#define DisposeElement_func_02070c08 ((void (*)(void *)) func_02070c08)

#define DisposeElement_func_02070be8 ((void (*)(void *)) func_02070be8)

void *func_ov139_02299b54(void *p)
{
    func_ov002_0220b10c(p);
    __cxa_vec_ctor((char *) p + 0xcc, 0x14, 0x6c, DisposeElement_func_02070c08, DisposeElement_func_02070be8);
    func_020b9cfc((char *) p + 0x93c);
    return p;
}

#undef DisposeElement_func_02070c08
#undef DisposeElement_func_02070be8
