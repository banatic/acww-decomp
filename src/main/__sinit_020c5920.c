/* __sinit_020c5920 @ 0x020c5920, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205e678(void *);
extern void __register_global_object(void *, void *, void *);
extern int data_021c9f5c;
extern int func_0205e65c;
extern int data_021c9f3c;

void __sinit_020c5920(void)
{
    func_0205e678((void *) &data_021c9f5c);
    __register_global_object((void *) &data_021c9f5c, (void *) &func_0205e65c, (void *) &data_021c9f3c);
}
