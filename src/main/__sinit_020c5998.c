/* __sinit_020c5998 @ 0x020c5998, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205f954(void *);
extern void __register_global_object(void *, void *, void *);
extern int data_021cacec;
extern void func_0205f950(void *);
extern int data_021cace0;

void __sinit_020c5998(void)
{
    func_0205f954((void *) &data_021cacec);
    __register_global_object((void *) ((void *) &data_021cacec), (((void *) func_0205f950)),
                             (void *) ((void *) &data_021cace0));
}
