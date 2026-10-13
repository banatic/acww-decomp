/* func_0207a264 @ 0x0207a264, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cf74(int c);

void func_0207a264(char *s, int c)
{
    int i;

    if (func_0207cf74(c)) {
        for (i = 0; i < 8; i++) {
            if (c == s[i]) {
                while (i < 7) {
                    s[i] = s[i + 1];
                    i++;
                }
                s[7] = -1;
                return;
            }
        }
    }
}
