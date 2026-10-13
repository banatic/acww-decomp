/* func_0207500c @ 0x0207500c, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0207500c(int a, int b)
{
    int diff;

    if (b < 0) {
        return 0;
    }
    if (a < 0) {
        return 1;
    }

    diff = a - b;
    if (diff == 0) {
        goto ret1;
    }
    if (diff > 0x3fff) {
        diff -= 0x7fff;
    } else if (diff < -0x3fff) {
        diff = 0x7fff - diff;
    }
    if (diff <= 0) {
        goto ret1;
    }
    return 0;

ret1:
    return 1;
}
