/* func_0205340c @ 0x0205340c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02053448(char *address);

int func_0205340c(char *base, int index)
{
    if (index < 4) {
        int offset = index * 20;
        return func_02053448(base + offset);
    }
    return 0;
}
