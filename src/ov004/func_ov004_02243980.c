/* func_ov004_02243980 @ 0x02243980, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(void);

int func_ov004_02243980(void)
{
    switch (func_020644cc()) {
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
