/* func_ov111_0229f6a8 @ 0x0229f6a8, 0x2c bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov111_0229f660(void *);
extern int func_ov095_0229b058(void *p);

int func_ov111_0229f6a8(void *self)
{
    if (*(unsigned char *) ((char *) self + 0x9b) != 0) {
        return 0;
    }
    if (func_ov095_0229b058((char *) self + 0xac) != 0) {
        return func_ov111_0229f660(self);
    }
    return 0;
}
