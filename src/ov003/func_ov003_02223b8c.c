/* func_ov003_02223b8c @ 0x02223b8c, 0x88 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *a, int b, int c, void *d, void *e);
extern void *func_ov003_02223b18(void *unused0);
extern void *func_ov003_02223c14(void *unused0);

#define VisitElement_ov003_02223c14 func_ov003_02223c14
#define VisitElement_ov003_02223b18 func_ov003_02223b18

char *func_ov003_02223b8c(char *param)
{
    char *p;

    __cxa_vec_ctor(param, 12, 0x14c, VisitElement_ov003_02223c14, VisitElement_ov003_02223b18);
    __cxa_vec_ctor(param + 0xf90, 4, 0x14c, VisitElement_ov003_02223c14, VisitElement_ov003_02223b18);
    __cxa_vec_ctor(param + 0x14c0, 3, 0x14c, VisitElement_ov003_02223c14, VisitElement_ov003_02223b18);
    __cxa_vec_ctor(param + 0x18a4, 4, 0x14c, VisitElement_ov003_02223c14, VisitElement_ov003_02223b18);
    p = param + 0x1dd4;
    do {
        *(int *) (p + 8) = 0;
        *(int *) (p + 12) = 0;
        p += 0x18;
    } while (p != param + 0x1e4c);
    return param;
}

#undef VisitElement_ov003_02223c14
#undef VisitElement_ov003_02223b18
