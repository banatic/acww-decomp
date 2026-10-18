/* __sinit_ov003_02237ee8 @ 0x02237ee8, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void *, void *);
extern void __register_global_object(void *object, void *destructor, void *node);
extern unsigned char data_ov003_02262aa8;
extern void func_ov003_02235d84(void);
extern void func_ov003_02235d80(void);
extern void func_ov003_02235d60(void);
extern unsigned char data_ov003_02262a9c;

#define DestroyGlobal_ov003_02235d60 ((void *) &func_ov003_02235d60)

#define VisitElement_ov003_02235d84 (void *) &func_ov003_02235d84
#define VisitElement_ov003_02235d80 (void *) &func_ov003_02235d80

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_ov003_02237ee8(void)
{
    __cxa_vec_ctor((void *) &data_ov003_02262aa8, 8, 16, VisitElement_ov003_02235d84, VisitElement_ov003_02235d80);
    __register_global_object(0, DestroyGlobal_ov003_02235d60, (void *) &data_ov003_02262a9c);
}

#undef DestroyGlobal_ov003_02235d60

#undef VisitElement_ov003_02235d84
#undef VisitElement_ov003_02235d80

#pragma section INIT end
