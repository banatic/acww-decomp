/* __sinit_020c5c94 @ 0x020c5c94, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020728e8(void *);
extern void __register_global_object(void *, void *, void *);
extern char *func_020727ec(void *);
extern int func_02072360(void *);
extern unsigned char data_021d0800;
extern int func_020728d8(void *);
extern unsigned char data_021d04bc;
extern unsigned char data_021d0504;
extern void *func_020727d4(void *);
extern unsigned char data_021d04a4;
extern unsigned char data_021d04c8;
extern int func_02072350(void *);
extern unsigned char data_021d04b0;

void __sinit_020c5c94(void)
{
    func_020728e8((void *) &data_021d0800);
    __register_global_object((void *) ((void *) &data_021d0800), (((void *) func_020728d8)),
                             (void *) ((void *) &data_021d04bc));
    func_020727ec((void *) &data_021d0504);
    __register_global_object((void *) ((void *) &data_021d0504), (((void *) func_020727d4)),
                             (void *) ((void *) &data_021d04a4));
    func_02072360((void *) &data_021d04c8);
    __register_global_object((void *) ((void *) &data_021d04c8), (((void *) func_02072350)),
                             (void *) ((void *) &data_021d04b0));
}
