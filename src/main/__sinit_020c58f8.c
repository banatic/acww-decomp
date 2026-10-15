/* __sinit_020c58f8 @ 0x020c58f8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0205e034(void *);
extern void __register_global_object(void *, void *, void *);
extern int data_021c9e68;
extern void *func_0205e018(void *);
extern int data_021c9e48;

void __sinit_020c58f8(void)
{
    func_0205e034((void *) &data_021c9e68);
    __register_global_object((void *) ((void *) &data_021c9e68), (((void *) func_0205e018)),
                             (void *) ((void *) &data_021c9e48));
}
