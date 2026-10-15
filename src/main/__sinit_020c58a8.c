/* __sinit_020c58a8 @ 0x020c58a8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205dc38(void *);
extern void __register_global_object(void *, void *, void *);
extern int data_021c9df4;
extern void func_0205dc34(void *);
extern int data_021c9de8;

void __sinit_020c58a8(void)
{
    func_0205dc38((void *) &data_021c9df4);
    __register_global_object((void *) ((void *) &data_021c9df4), (((void *) func_0205dc34)),
                             (void *) ((void *) &data_021c9de8));
}
