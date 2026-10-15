/* __sinit_020c6394 @ 0x020c6394, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020985a0(void *);
extern void __register_global_object(void *, void *, void *);
extern int data_021d5738;
extern int func_02098580(void *);
extern int data_021d56fc;

void __sinit_020c6394(void)
{
    func_020985a0((void *) &data_021d5738);
    __register_global_object((void *) ((void *) &data_021d5738), (((void *) func_02098580)),
                             (void *) ((void *) &data_021d56fc));
}
