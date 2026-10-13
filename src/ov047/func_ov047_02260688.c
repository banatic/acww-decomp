/* func_ov047_02260688 @ 0x02260688, 0x14 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

void func_ov047_02260688(void *r0, int r1)
{
    if (r1 == 0) {
        *(int *) ((char *) r0 + 0xd0) = 0x14;
    } else {
        *(int *) ((char *) r0 + 0xd0) = 0x28;
    }
}
