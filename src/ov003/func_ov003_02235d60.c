/* func_ov003_02235d60 @ 0x02235d60, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02235d80(void);
extern void __cxa_vec_cleanup(void *a, int b, int c, void (*d)(void));

extern unsigned char data_ov003_02262aa8[];

#define VisitElement_ov003_02235d80 func_ov003_02235d80

void func_ov003_02235d60(void)
{
    __cxa_vec_cleanup((void *) data_ov003_02262aa8, 8, 0x10, VisitElement_ov003_02235d80);
}

#undef VisitElement_ov003_02235d80
