/* func_ov004_0220cdd8 @ 0x0220cdd8, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

int func_ov004_0220cdd8(void *self, int id)
{
    if (*(int *) ((char *) self + 0x534) == id) {
        return 1;
    } else {
        return 0;
    }
}
