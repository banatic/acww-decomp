/* __sinit_ov003_02237e48 @ 0x02237e48, 0xa0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void *, void *);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_ov003_022617bc;
extern void func_ov003_0222d57c(void);
extern void func_ov003_0222d520(void);
extern void func_ov003_02235c10(void);
extern unsigned char data_ov003_02260564;
extern unsigned char data_ov003_02260994;
extern void func_ov003_02235bec(void);
extern unsigned char data_ov003_02260570;
extern unsigned char data_ov003_02260e4c;
extern void func_ov003_02235bc8(void);
extern unsigned char data_ov003_0226057c;
extern unsigned char data_ov003_02260558;
extern void func_020012dc(void);
extern unsigned char data_ov003_02260588;

void __sinit_ov003_02237e48(void)
{
    __cxa_vec_ctor((void *) &data_ov003_022617bc, 8, 604, (void *) &func_ov003_0222d57c, (void *) &func_ov003_0222d520);
    __register_global_object(0, (void *) &func_ov003_02235c10, (void *) &data_ov003_02260564);
    __cxa_vec_ctor((void *) &data_ov003_02260994, 2, 604, (void *) &func_ov003_0222d57c, (void *) &func_ov003_0222d520);
    __register_global_object(0, (void *) &func_ov003_02235bec, (void *) &data_ov003_02260570);
    __cxa_vec_ctor((void *) &data_ov003_02260e4c, 4, 604, (void *) &func_ov003_0222d57c, (void *) &func_ov003_0222d520);
    __register_global_object(0, (void *) &func_ov003_02235bc8, (void *) &data_ov003_0226057c);
    __register_global_object((void *) &data_ov003_02260558, (void *) &func_020012dc, (void *) &data_ov003_02260588);
}
