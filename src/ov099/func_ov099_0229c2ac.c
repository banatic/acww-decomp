/* func_ov099_0229c2ac @ 0x0229c2ac, 0x18 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

int func_ov099_0229c2ac(void *self, int mask)
{
    if (*(unsigned int *) ((char *) self + 0x27e8) & mask) {
        return 1;
    }
    return 0;
}
