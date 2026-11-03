/* sound_6: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020046b4 @ 0x020046b4, 0x10 bytes, Thumb
 * func_020046a4 @ 0x020046a4, 0x10 bytes, Thumb
 */

extern void func_020f2378(void *receiver);
extern void func_020f2368(void *ptr);
extern unsigned char data_021fd1bc[];

void func_020046b4(void)
{
    func_020f2378(((char *) data_021fd1bc));
}

void func_020046a4(void)
{
    func_020f2368((void *) data_021fd1bc);
}
