/* func_ov130_0229a790 @ 0x0229a790, 0x1c bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern int **func_02070be8(void *unused0);

#define VisitElement_02070be8 (void (*)(void *)) func_02070be8

void *func_ov130_0229a790(void *arg)
{
    __cxa_vec_cleanup((char *) arg + 0x2c, 5, 0x6c, VisitElement_02070be8);
    return arg;
}

#undef VisitElement_02070be8
