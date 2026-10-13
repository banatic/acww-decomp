/* func_ov002_022088f0 @ 0x022088f0, 0x12 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022088f0(void *self);

int func_ov002_022088f0(void *self)
{
    if ((*(unsigned char *) ((char *) self + 0x10) & 0x20) != 0) {
        return 1;
    }
    return 0;
}
