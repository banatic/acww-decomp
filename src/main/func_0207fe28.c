/* func_0207fe28 @ 0x0207fe28, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207ffa0(int a, int b);
extern int func_0207cc54(int a, int b, int c);

int func_0207fe28(int a, int b, int c)
{
    if (func_0207ffa0(a, b) != 0) {
        unsigned short *ptr = (unsigned short *) (a + 0x78c) + b;
        unsigned short bits = 0;
        int count = 0;

        while (b < c) {
            if (func_0207ffa0(a, b) != 0) {
                if (*ptr == 0xfff1) {
                    bits |= (1 << b);
                    count++;
                }
            }
            ptr++;
            b++;
        }
        return func_0207cc54(bits, count, 10);
    } else {
        return -1;
    }
}
