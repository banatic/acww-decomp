/* angle_sector: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02064594 @ 0x02064594, 0x28 bytes, Thumb
 * func_02064558 @ 0x02064558, 0x3c bytes, Thumb
 * func_020644e4 @ 0x020644e4, 0x74 bytes, Thumb
 */

int func_02064594(int r0)
{
    if (r0 > 0 && r0 < 0x8000) {
        return 0;
    }
    if (r0 > -0x8000 && r0 < 0) {
        return 1;
    }
    return 2;
}

int func_02064558(int r0)
{
    if (r0 <= -0x6000) {
        return 2;
    }
    if (r0 <= -0x2000) {
        return 3;
    }
    if (r0 <= 0x2000) {
        return 0;
    }
    if (r0 <= 0x6000) {
        return 1;
    }
    return 2;
}

int func_020644e4(int r0)
{
    if (r0 <= -30038) {
        return 4;
    }
    if (r0 <= -19114) {
        return 5;
    }
    if (r0 <= -13654) {
        return 6;
    }
    if (r0 <= -2730) {
        return 7;
    }
    if (r0 <= 2730) {
        return 0;
    }
    if (r0 <= 13654) {
        return 1;
    }
    if (r0 <= 19114) {
        return 2;
    }
    if (r0 <= 30038) {
        return 3;
    }
    return 4;
}
