/* __sinit_020c5970 @ 0x020c5970, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205f7fc(void *);
extern void __register_global_object(void *, void *, void *);
extern int data_021cacd0;
extern int func_0205f7f8;
extern int data_021cacc4;

void __sinit_020c5970(void)
{
    func_0205f7fc((void *) &data_021cacd0);
    __register_global_object((void *) &data_021cacd0, (void *) &func_0205f7f8, (void *) &data_021cacc4);
}
