/* func_ov003_0222c454 @ 0x0222c454, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov003_0225f35c[];
void __cxa_vec_cleanup(void *p, int n, int sz, void (*dtor)(void *));
void *func_ov003_0222c3d0(void *p);

#define VisitElement_ov003_0222c3d0 (void (*)(void *p)) func_ov003_0222c3d0

void func_ov003_0222c454(void *object)
{
    (void) object;
    __cxa_vec_cleanup(data_ov003_0225f35c, 4, 0x60, VisitElement_ov003_0222c3d0);
}

#undef VisitElement_ov003_0222c3d0
