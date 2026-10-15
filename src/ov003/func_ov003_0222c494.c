/* func_ov003_0222c494 @ 0x0222c494, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov003_0225f76c[];
void __cxa_vec_cleanup(void *p, int n, int sz, void (*dtor)(void *));
void *func_ov003_02228fe8(void *p);

#define VisitElement_ov003_02228fe8 (void (*)(void *p)) func_ov003_02228fe8

void func_ov003_0222c494(void *object)
{
    (void) object;
    __cxa_vec_cleanup(data_ov003_0225f76c, 6, 0x24c, VisitElement_ov003_02228fe8);
}

#undef VisitElement_ov003_02228fe8
