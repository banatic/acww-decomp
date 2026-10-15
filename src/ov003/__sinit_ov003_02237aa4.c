/* __sinit_ov003_02237aa4 @ 0x02237aa4, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void *, void *);
extern void __register_global_object(void *object, void *destructor, void *node);
extern unsigned char data_ov003_0223cfe4;
extern void *func_ov003_022275ec(void *element);
extern void *func_ov003_022275d8(void *element);
extern void *func_ov003_022275bc(void *object);
extern unsigned char data_ov003_0223cf7c;
extern unsigned char data_ov003_0223cf88;
extern void func_020012dc(void *object);
extern unsigned char data_ov003_0223cf94;

#define DestroyGlobal_ov003_022275bc ((void *) &func_ov003_022275bc)
#define DestroyGlobal_020012dc ((void *) &func_020012dc)
#define VisitElement_ov003_022275ec (void (*)(void *)) func_ov003_022275ec
#define VisitElement_ov003_022275d8 (void (*)(void *)) func_ov003_022275d8

void __sinit_ov003_02237aa4(void)
{
    __cxa_vec_ctor((void *) &data_ov003_0223cfe4, 20, 164, VisitElement_ov003_022275ec, VisitElement_ov003_022275d8);
    __register_global_object((void *) &data_ov003_0223cfe4, DestroyGlobal_ov003_022275bc, (void *) &data_ov003_0223cf7c);
    __register_global_object((void *) &data_ov003_0223cf88, DestroyGlobal_020012dc, (void *) &data_ov003_0223cf94);
}

#undef DestroyGlobal_ov003_022275bc
#undef DestroyGlobal_020012dc
#undef VisitElement_ov003_022275ec
#undef VisitElement_ov003_022275d8
