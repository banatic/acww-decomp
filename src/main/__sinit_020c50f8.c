/* __sinit_020c50f8 @ 0x020c50f8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern unsigned char data_021c72e8;
extern void func_0203f598(void *);

void __sinit_020c50f8(void)
{
    __cxa_vec_ctor((void *) ((void *) &data_021c72e8), 15, 28, (void (*)(void *)) func_0203f598, 0);
}
