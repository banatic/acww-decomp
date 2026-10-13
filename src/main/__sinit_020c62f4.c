/* __sinit_020c62f4 @ 0x020c62f4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208fae8(void *);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_021d3654;
extern void func_0208fac4(void);
extern unsigned char data_021d3628;

void __sinit_020c62f4(void)
{
    func_0208fae8((void *) &data_021d3654);
    __register_global_object((void *) &data_021d3654, (void *) &func_0208fac4, (void *) &data_021d3628);
}
