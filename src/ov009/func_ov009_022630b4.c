/* func_ov009_022630b4 @ 0x022630b4, 0x30 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov009_022630e4(void *ptr);

void func_ov009_022630b4(void *ptr)
{
    ((unsigned char *) ptr)[0x235] &= ~1;
    if (func_ov009_022630e4(ptr)) {
        ((unsigned char *) ptr)[0x235] |= 1;
    }
}
