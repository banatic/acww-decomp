/* __sinit_020c58d0 @ 0x020c58d0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205dd54(void *);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_021c9e24;
extern void func_0205dd50(void *);
extern unsigned char data_021c9e18;

void __sinit_020c58d0(void)
{
    func_0205dd54((void *) &data_021c9e24);
    __register_global_object((void *) ((void *) &data_021c9e24), (((void *) func_0205dd50)),
                             (void *) ((void *) &data_021c9e18));
}
