/* func_ov003_0222c474 @ 0x0222c474, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov003_0225f4dc[];
void __cxa_vec_cleanup(void *p, int n, int sz, void (*dtor)(void *));
void *func_ov003_02228ec4(void *p);

#define VisitElement_ov003_02228ec4 (void (*)(void *p)) func_ov003_02228ec4

void func_ov003_0222c474(void *object)
{
    (void) object;
    __cxa_vec_cleanup(data_ov003_0225f4dc, 4, 0xa4, VisitElement_ov003_02228ec4);
}

#undef VisitElement_ov003_02228ec4
