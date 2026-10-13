/* func_ov111_0229fdf0 @ 0x0229fdf0, 0x1c bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8fb8(void);

void func_ov111_0229fdf0(void *self)
{
    if (*(int *) ((char *) self + 0xa8) != 0) {
        func_020a8fb8();
        *(int *) ((char *) self + 0xa8) = 0;
    }
}
