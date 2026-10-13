/* func_ov118_0229b374 @ 0x0229b374, 0x1a bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_ov118_0229b390(void);

unsigned int func_ov118_0229b374(void)
{
    unsigned int t;

    t = func_ov118_0229b390();
    if (t <= 6) {
        return 0;
    } else {
        return (t - 6) << 4;
    }
}
