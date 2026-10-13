/* func_020882b0 @ 0x020882b0, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020882b0(unsigned char *ptr, unsigned int flag)

{

    ptr[0xe] = (ptr[0xe] & ~0x10) | ((flag & 1) << 4);
}
