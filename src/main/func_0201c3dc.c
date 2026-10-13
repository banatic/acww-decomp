/* func_0201c3dc @ 0x0201c3dc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201c3dc(int r0);

int func_0201c3dc(int r0)
{
    if (r0 < 0) {
        r0 = -r0;
    }
    if (r0 < 0x4000) {
        return 1;
    }
    return 0;
}
