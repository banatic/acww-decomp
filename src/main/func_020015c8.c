/* func_020015c8 @ 0x020015c8, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_0213fdd0;
extern unsigned int data_0213fddc;
extern void func_020015fc(unsigned int, unsigned int, unsigned int);

void func_020015c8(void)
{
    unsigned int a;
    a = data_0213fddc;
    func_020015fc(0x007f007f, data_0213fdd0, 0x00000800);
    func_020015fc(0x007f007f, a, 0x00000800);
}
