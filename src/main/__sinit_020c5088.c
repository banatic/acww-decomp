/* __sinit_020c5088 @ 0x020c5088, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203d2c4(void *);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_021c6998;
extern void func_0203d2b4(void);
extern unsigned char data_021c699c;

void __sinit_020c5088(void)
{
    func_0203d2c4((void *) &data_021c6998);
    __register_global_object((void *) &data_021c6998, (void *) &func_0203d2b4, (void *) &data_021c699c);
}
