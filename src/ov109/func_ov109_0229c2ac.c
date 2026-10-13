/* func_ov109_0229c2ac @ 0x0229c2ac, 0x18 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

int func_ov109_0229c2ac(void *ptr, int mask)
{
    if (*(int *) ((char *) ptr + 0x29b4) & mask) {
        return 1;
    }
    return 0;
}
