/* __sinit_ov003_02237e48 @ 0x02237e48, 0xa0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void *, void *);
extern void __register_global_object(void *object, void *destructor, void *node);
extern unsigned char data_ov003_022617bc;
extern void *func_ov003_0222d57c(void *element);
extern void *func_ov003_0222d520(void *element);
extern void func_ov003_02235c10(void *object);
extern unsigned char data_ov003_02260564;
extern unsigned char data_ov003_02260994;
extern void func_ov003_02235bec(void *object);
extern unsigned char data_ov003_02260570;
extern unsigned char data_ov003_02260e4c;
extern void func_ov003_02235bc8(void *object);
extern unsigned char data_ov003_0226057c;
extern unsigned char data_ov003_02260558;
extern void func_020012dc(void *object);
extern unsigned char data_ov003_02260588;

#define DestroyGlobal_ov003_02235c10 ((void *) &func_ov003_02235c10)
#define DestroyGlobal_ov003_02235bec ((void *) &func_ov003_02235bec)
#define DestroyGlobal_ov003_02235bc8 ((void *) &func_ov003_02235bc8)
#define DestroyGlobal_020012dc ((void *) &func_020012dc)
#define VisitElement_ov003_0222d57c (void (*)(void *)) func_ov003_0222d57c
#define VisitElement_ov003_0222d520 (void (*)(void *)) func_ov003_0222d520

void __sinit_ov003_02237e48(void)
{
    __cxa_vec_ctor((void *) &data_ov003_022617bc, 8, 604, VisitElement_ov003_0222d57c, VisitElement_ov003_0222d520);
    __register_global_object(0, DestroyGlobal_ov003_02235c10, (void *) &data_ov003_02260564);
    __cxa_vec_ctor((void *) &data_ov003_02260994, 2, 604, VisitElement_ov003_0222d57c, VisitElement_ov003_0222d520);
    __register_global_object(0, DestroyGlobal_ov003_02235bec, (void *) &data_ov003_02260570);
    __cxa_vec_ctor((void *) &data_ov003_02260e4c, 4, 604, VisitElement_ov003_0222d57c, VisitElement_ov003_0222d520);
    __register_global_object(0, DestroyGlobal_ov003_02235bc8, (void *) &data_ov003_0226057c);
    __register_global_object((void *) &data_ov003_02260558, DestroyGlobal_020012dc, (void *) &data_ov003_02260588);
}

#undef DestroyGlobal_ov003_02235c10
#undef DestroyGlobal_ov003_02235bec
#undef DestroyGlobal_ov003_02235bc8
#undef DestroyGlobal_020012dc
#undef VisitElement_ov003_0222d57c
#undef VisitElement_ov003_0222d520
