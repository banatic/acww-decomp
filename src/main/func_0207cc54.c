/* func_0207cc54 @ 0x0207cc54, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);

int func_0207cc54(unsigned int a, int b, int c)
{
    int count;
    int i;
    if (b > 0) {
        count = func_020644cc(b);
        for (i = 0; i < c; i++) {
            if ((a >> i) & 1) {
                if (count == 0) {
                    return i;
                }
                count--;
            }
        }
    }
    return -1;
}
