/* func_020abd68 @ 0x020abd68, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200467c(int command);

void func_020abd68(unsigned char *ptr, unsigned char value, int flag)
{
    if (flag != 0 && *(ptr + 0x145) == 0 && value != 0) {
        func_0200467c(0x3b);
    }
    *(ptr + 0x145) = value;
}
