/* func_ov119_0229bfa4 @ 0x0229bfa4, 0x38 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(int);
extern int func_ov119_0229b188(int);
extern void func_ov119_0229b7e8(int);

void func_ov119_0229bfa4(int r0)
{
    int r4 = r0;
    int r1;

    if (func_0208e484(r4 + 0xda8) != 0) {
        r1 = func_ov119_0229b188(r4);
        if (r1 == 1) {
            return;
        }
        if (r1 == 2) {
            func_ov119_0229b7e8(r4);
            return;
        }
        func_ov119_0229b7e8(r4);
    }
}
