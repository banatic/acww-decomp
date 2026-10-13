/* func_02018714 @ 0x02018714, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02057d0c(int param);

void func_02018714(unsigned char *p, unsigned int *q)
{
    unsigned int val;

    val = q[0x64];
    if (((val << 4) >> 16) == 0x17) {
        func_02057d0c(2);
        p[0x98] = 4;
    }
}
