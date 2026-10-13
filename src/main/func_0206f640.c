/* func_0206f640 @ 0x0206f640, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fbf8(int, int, int, int);
extern void func_0206fc1c(int, int);

int func_0206f640(int p0, int p1, int p2, int p3)
{
    if (func_0206fbf8(p0, p1, p2, p3)) {
        func_0206fc1c(p1, p2);
        return 1;
    } else {
        return 0;
    }
}
