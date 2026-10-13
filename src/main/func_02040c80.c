/* func_02040c80 @ 0x02040c80, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02040c90(void *ptr, int value);

extern unsigned char data_021f39c0[];

void func_02040c80(void)
{
    func_02040c90((void *) data_021f39c0, 0);
}
