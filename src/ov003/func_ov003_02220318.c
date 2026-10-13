/* func_ov003_02220318 @ 0x02220318, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_02220174(int);
extern int func_ov009_02262fd8(void);

int func_ov003_02220318(int a)
{
    unsigned short x = (unsigned short) (a + 0x5001);
    if (func_ov003_02220174(x) != 0) {
        return func_ov009_02262fd8();
    }
    return 0;
}
