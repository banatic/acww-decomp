/* func_ov047_0226076c @ 0x0226076c, 0x14 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov047_0226076c(int *r0, int r1);

void func_ov047_0226076c(int *r0, int r1)
{
    if (r1 == 0) {
        *(int *) ((char *) r0 + 0xd0) = 0x14;
    } else {
        *(int *) ((char *) r0 + 0xd0) = 0x28;
    }
}
