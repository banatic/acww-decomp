/* func_ov133_0229bde8 @ 0x0229bde8, 0x38 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(int);
extern int func_ov133_0229b44c(int);
extern void func_ov133_0229b958(int);

void func_ov133_0229bde8(int r0)
{
    int r4 = r0;
    int r1;

    if (func_0208e484(r4 + 0x11c) != 0) {
        r1 = func_ov133_0229b44c(r4);
        if (r1 == 1) {
            return;
        }
        if (r1 == 2) {
            func_ov133_0229b958(r4);
            return;
        }
        func_ov133_0229b958(r4);
    }
}
