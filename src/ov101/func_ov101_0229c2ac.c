/* func_ov101_0229c2ac @ 0x0229c2ac, 0x12 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov101_0229c2ac(int r0, int r1);

int func_ov101_0229c2ac(int r0, int r1)
{
    if ((*(int *) (r0 + 0x94) & r1) != 0) {
        return 1;
    }
    return 0;
}
