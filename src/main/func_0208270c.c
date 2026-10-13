/* func_0208270c @ 0x0208270c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02082854(void *base, unsigned short *key);

int func_0208270c(void *base, unsigned short *key)
{
    int result = 0;
    int index;
    unsigned short val;

    val = *key;
    if (((val & 0xf000) >> 12) == 0xd) {
        index = func_02082854(base, key);
        if (index >= 0 && index < 4) {
            result = *(int *) ((unsigned char *) base + (index * 8) + 0x40);
        }
    }
    return result;
}
