/* __sinit_020c5154 @ 0x020c5154, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204086c(void *);
extern void __register_global_object(void *, void *, void *);
extern int data_021c74d0;
extern void func_02040868(void *);
extern int data_021c74b8;
extern int data_021c7528;
extern int data_021c74c4;

void __sinit_020c5154(void)
{
    func_0204086c((void *) &data_021c74d0);
    __register_global_object((void *) ((void *) &data_021c74d0), (((void *) func_02040868)),
                             (void *) ((void *) &data_021c74b8));
    func_0204086c((void *) &data_021c7528);
    __register_global_object((void *) ((void *) &data_021c7528), (((void *) func_02040868)),
                             (void *) ((void *) &data_021c74c4));
}
