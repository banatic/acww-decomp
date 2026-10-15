/* __sinit_020c5cf4 @ 0x020c5cf4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02073fcc(void *);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_021d0a44;
extern void func_02073fc8(void *);
extern unsigned char data_021d0a38;

void __sinit_020c5cf4(void)
{
    func_02073fcc((void *) &data_021d0a44);
    __register_global_object((void *) ((void *) &data_021d0a44), (((void *) func_02073fc8)),
                             (void *) ((void *) &data_021d0a38));
}
