/* func_020019f4 @ 0x020019f4, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_0213fe94[];

void func_020019f4(void)
{
    unsigned char *ptr;
    unsigned char val;

    ptr = data_0213fe94;
    val = ptr[0x12];
    val |= 2;
    ptr[0x12] = val;
}
