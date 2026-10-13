/* func_020a5bc4 @ 0x020a5bc4, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020a5bc4(char *base, int idx, int v)
{
    *(int *) (base + idx * 4 + 0xa8) = v;
}
