/* func_020adde4 @ 0x020adde4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020addd0(int);

int func_020adde4(unsigned int arg)
{
    int i;
    for (i = 4; i >= 0; i--) {
        if (arg >= func_020addd0(i)) {
            return i;
        }
    }
    return 0;
}
