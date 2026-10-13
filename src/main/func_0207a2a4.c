/* func_0207a2a4 @ 0x0207a2a4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cf74(int);

void func_0207a2a4(char *a, int b)
{
    if (func_0207cf74(b)) {
        int i;
        char *p = a;
        for (i = 0; i < 8; i++) {
            if (*p == -1) {
                *p = b;
                break;
            }
            p++;
        }
    }
}
