/* __sinit_020c6c54 @ 0x020c6c54, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020ab960(void *);
extern void __register_global_object(void *, void *, void *);
extern int data_021f4670;
extern void *func_020ab948(void *);
extern int data_021f45b4;

void __sinit_020c6c54(void)
{
    func_020ab960((void *) &data_021f4670);
    __register_global_object((void *) ((void *) &data_021f4670), (((void *) func_020ab948)),
                             (void *) ((void *) &data_021f45b4));
}
