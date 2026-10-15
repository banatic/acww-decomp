/* __sinit_020c6e10 @ 0x020c6e10, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020b40dc(void *);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_021f4dac;
extern void *func_020b4070(void *);
extern unsigned char data_021f4c80;

void __sinit_020c6e10(void)
{
    func_020b40dc((void *) &data_021f4dac);
    __register_global_object((void *) ((void *) &data_021f4dac), (((void *) func_020b4070)),
                             (void *) ((void *) &data_021f4c80));
}
