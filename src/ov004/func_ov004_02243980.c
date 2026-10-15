/* func_ov004_02243980 @ 0x02243980, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int parameter0);

int func_ov004_02243980(int arg0)
{
    switch (func_020644cc(arg0)) {
        case 0:
            return 0xaaa;
        case 1:
            return 0x1554;
        case 2:
            return 0x2000;
        case 3:
            return 0x2aaa;
        case 4:
            return -0xaaa;
        case 5:
            return -0x1554;
        case 6:
            return -0x2000;
    }
    return -0x2aaa;
}
