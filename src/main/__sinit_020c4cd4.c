/* __sinit_020c4cd4 @ 0x020c4cd4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02037ae8(void *);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_021c52c0;
extern void func_02037ae4(void);
extern unsigned char data_021c52b4;

void __sinit_020c4cd4(void)
{
    func_02037ae8((void *) &data_021c52c0);
    __register_global_object((void *) &data_021c52c0, (void *) &func_02037ae4, (void *) &data_021c52b4);
}
