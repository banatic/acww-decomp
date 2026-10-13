/* __sinit_020c4a80 @ 0x020c4a80, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066694(void *);
extern void __register_global_object(void *, void *, void *);
extern int data_021c2604;
extern int func_02066688;
extern int data_021c1d28;

void __sinit_020c4a80(void)
{
    func_02066694((void *) &data_021c2604);
    __register_global_object((void *) &data_021c2604, (void *) &func_02066688, (void *) &data_021c1d28);
}
