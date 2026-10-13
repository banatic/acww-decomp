/* func_0206f258 @ 0x0206f258, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021cfc20;

int func_0206f258(void)
{
    unsigned short u;
    u = data_021cfc20;
    u = (unsigned short) (u + 0xfffb);
    if (u > 2) {
        return 0;
    }
    return 1;
}
