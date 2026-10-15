/* __sinit_020c511c @ 0x020c511c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0203f728(void *);
extern void __register_global_object(void *, void *, void *);
extern struct B021c748c {
    int unk_00;
} data_021c748c;
extern int data_020ca0e8;
extern int data_021c749c;
extern void func_0203f724(void *);
extern int data_021c7490;

void __sinit_020c511c(void)
{
    data_021c748c.unk_00 = data_020ca0e8;
    func_0203f728((void *) &data_021c749c);
    __register_global_object((void *) ((void *) &data_021c749c), (((void *) func_0203f724)),
                             (void *) ((void *) &data_021c7490));
}
