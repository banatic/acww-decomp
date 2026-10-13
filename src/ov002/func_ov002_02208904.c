/* func_ov002_02208904 @ 0x02208904, 0x12 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

int func_ov002_02208904(unsigned char *p)
{
    if (p[0x10] & 0x80) {
        return 1;
    } else {
        return 0;
    }
}
