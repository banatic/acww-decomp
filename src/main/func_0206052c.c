/* func_0206052c @ 0x0206052c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0206052c(char *base, int index, int value)
{
    *(int *) (base + index * 4 + 0x750) = value;
}
