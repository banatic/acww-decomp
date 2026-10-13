/* func_02083f84 @ 0x02083f84, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083fa4(void *dst, const void *src, int size, int flag);

extern unsigned char data_020d0654[];
extern unsigned char data_020d0684[];

void func_02083f84(void)
{
    func_02083fa4((void *) data_020d0684, (const void *) data_020d0654, 4, 1);
}
