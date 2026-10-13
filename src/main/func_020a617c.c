/* func_020a617c @ 0x020a617c, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020a617c(char *base, int idx, int v)
{
    *(int *) (base + idx * 4 + 0x84) = v;
}
