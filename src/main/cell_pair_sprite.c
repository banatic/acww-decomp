/* cell_pair_sprite: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208a234 @ 0x0208a234, 0x4 bytes, Thumb
 * func_0208a20c @ 0x0208a20c, 0x26 bytes, Thumb
 */

extern int func_0208a160(int arg);

int func_0208a234(int *p0)
{
    return p0[13];
}

int func_0208a20c(int arg)
{
    if (func_0208a160(arg + 0xC) && func_0208a160(arg + 0x20)) {
        return 1;
    } else {
        return 0;
    }
}
