/* func_ov047_02260758 @ 0x02260758, 0x14 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov047_02260758(int *r0, int r1);

void func_ov047_02260758(int *r0, int r1)
{
    if (r1 == 0) {
        r0 = (int *) ((char *) r0 + 0xd0);
        *r0 = 0x2c;
    } else {
        r0 = (int *) ((char *) r0 + 0xd0);
        *r0 = 0x1f;
    }
}
