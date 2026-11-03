/* label_sprite_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208f0c0 @ 0x0208f0c0, 0x4 bytes, Thumb
 * func_0208f098 @ 0x0208f098, 0x26 bytes, Thumb
 */

extern int func_0208a160(char *ptr);

int func_0208f0c0(int *p0)
{
    return p0[17];
}

int func_0208f098(char *arg)
{
    return func_0208a160(arg + 0x1c) && func_0208a160(arg + 0x30);
}
