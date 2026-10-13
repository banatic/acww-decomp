/* __sinit_020c5830 @ 0x020c5830, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205d1b8(void *);
extern void __register_global_object(void *, void *, void *);
extern int data_021c9c2c;
extern int func_0205d19c;
extern int data_021c9c20;

void __sinit_020c5830(void)
{
    func_0205d1b8((void *) &data_021c9c2c);
    __register_global_object((void *) &data_021c9c2c, (void *) &func_0205d19c, (void *) &data_021c9c20);
}
