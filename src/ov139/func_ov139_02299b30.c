/* func_ov139_02299b30 @ 0x02299b30, 0x24 bytes, Thumb, module ov139
 * mwccarm 1.2/base -O4,s
 */

extern int **func_02070be8(void *element);
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void *func_ov002_0220b0f4(void *);

#define DisposeElement_func_02070be8 ((void (*)(void *)) func_02070be8)

void *func_ov139_02299b30(void *p)
{
    __cxa_vec_cleanup((char *) p + 0xCC, 0x14, 0x6C, DisposeElement_func_02070be8);
    func_ov002_0220b0f4(p);
    return p;
}

#undef DisposeElement_func_02070be8
