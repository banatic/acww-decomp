/* __sinit_ov003_02237aa4 @ 0x02237aa4, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void *, void *);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_ov003_0223cfe4;
extern void func_ov003_022275ec(void);
extern void func_ov003_022275d8(void);
extern void func_ov003_022275bc(void);
extern unsigned char data_ov003_0223cf7c;
extern unsigned char data_ov003_0223cf88;
extern void func_020012dc(void);
extern unsigned char data_ov003_0223cf94;

void __sinit_ov003_02237aa4(void)
{
    __cxa_vec_ctor((void *) &data_ov003_0223cfe4, 20, 164, (void *) &func_ov003_022275ec, (void *) &func_ov003_022275d8);
    __register_global_object((void *) &data_ov003_0223cfe4, (void *) &func_ov003_022275bc, (void *) &data_ov003_0223cf7c);
    __register_global_object((void *) &data_ov003_0223cf88, (void *) &func_020012dc, (void *) &data_ov003_0223cf94);
}
