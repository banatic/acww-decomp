/* __sinit_020c6f34 @ 0x020c6f34, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020b8d08(void *);
extern void __register_global_object(void *, void *, void *);
extern int data_021f6b20;
extern void *func_020b8cec(void *);
extern int data_021f6af4;

void __sinit_020c6f34(void)
{
    func_020b8d08((void *) &data_021f6b20);
    __register_global_object((void *) ((void *) &data_021f6b20), (((void *) func_020b8cec)),
                             (void *) ((void *) &data_021f6af4));
}
