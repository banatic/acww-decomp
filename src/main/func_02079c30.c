/* func_02079c30 @ 0x02079c30, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cf74(int);
extern int func_02079c74(char *, int, int);
extern int func_02079ca4(char *, int);

void func_02079c30(char *a, int b)
{
    int i;
    int v;
    if (func_0207cf74(b) != 0) {
        for (i = 0; i < 8; i++) {
            if (i == b) {
                continue;
            }
            v = func_02079c74(a, b, i);
            if (func_02079ca4(a, v) != 0) {
                a[v] = 0;
            }
        }
    }
}
