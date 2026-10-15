/* __sinit_020c5808 @ 0x020c5808, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205ce98(void *);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_021c9b58;
extern void func_0205ce94(void *);
extern unsigned char data_021c9b38;

void __sinit_020c5808(void)
{
    func_0205ce98((void *) &data_021c9b58);
    __register_global_object((void *) ((void *) &data_021c9b58), (((void *) func_0205ce94)),
                             (void *) ((void *) &data_021c9b38));
}
