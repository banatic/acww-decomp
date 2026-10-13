/* __sinit_020c4ac4 @ 0x020c4ac4, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202f8fc(void *, int, int);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_021c30b8;
extern void func_0202f2f0(void);
extern unsigned char data_021c30c0;

void __sinit_020c4ac4(void)
{
    func_0202f8fc((void *) &data_021c30b8, 0, 0);
    __register_global_object((void *) &data_021c30b8, (void *) &func_0202f2f0, (void *) &data_021c30c0);
}
