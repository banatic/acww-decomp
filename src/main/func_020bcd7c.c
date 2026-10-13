/* func_020bcd7c @ 0x020bcd7c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);

void func_020bcd7c(int *base, int *out)
{
    int val;
    val = base[0x2f48 / 4];
    if (val > 0) {
        val = func_020644cc(val);
    } else {
        val = 0;
    }
    *out = val + 0x41;
}
