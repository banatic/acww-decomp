/* func_ov104_0229c364 @ 0x0229c364, 0x12 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov104_0229c364(int r0, int r1);

int func_ov104_0229c364(int r0, int r1)
{
    if (*(int *) (r0 + 0x94) & r1) {
        return 1;
    }
    return 0;
}
