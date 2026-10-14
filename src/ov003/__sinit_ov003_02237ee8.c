/* __sinit_ov003_02237ee8 @ 0x02237ee8, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void *, void *);
extern void __register_global_object(int, void *, void *);
extern unsigned char data_ov003_02262aa8;
extern void func_ov003_02235d84(void);
extern void func_ov003_02235d80(void);
extern void func_ov003_02235d60(void);
extern unsigned char data_ov003_02262a9c;

void __sinit_ov003_02237ee8(void)
{
    __cxa_vec_ctor((void *) &data_ov003_02262aa8, 8, 16, (void *) &func_ov003_02235d84, (void *) &func_ov003_02235d80);
    __register_global_object(0, (void *) &func_ov003_02235d60, (void *) &data_ov003_02262a9c);
}
