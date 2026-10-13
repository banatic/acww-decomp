/* func_ov110_0229c2c8 @ 0x0229c2c8, 0x12 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229c2c8(int param1, int param2);

int func_ov110_0229c2c8(int param1, int param2)
{
    if ((*(int *) (param1 + 0x94) & param2) != 0) {
        return 1;
    }
    return 0;
}
