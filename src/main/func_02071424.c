/* func_02071424 @ 0x02071424, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_02071318(int a, int b, int *out);

void func_02071424(int a, int b)
{
    int out;
    unsigned char *p = func_02071318(a, b, &out);
    if (p) {
        p[out >> 1] &= ~(0xF << ((out & 1) << 2));
    }
}
