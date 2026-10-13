/* func_ov118_0229b3b0 @ 0x0229b3b0, 0x28 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov118_0229a460(int a, int b);

int func_ov118_0229b3b0(int a)
{
    int result;
    if (func_ov118_0229a460(a, 1)) {
        result = a + 0x4797;
    } else {
        result = a + 0x478a;
    }
    return result;
}
