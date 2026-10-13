/* func_ov134_022999e0 @ 0x022999e0, 0x1e bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a4f8(void *);

int func_ov134_022999e0(void *self)
{
    if (*(unsigned char *) ((char *) self + 0xb0) == 0) {
        return func_ov002_0220a4f8((char *) self + 0x18);
    }
    return *(int *) ((char *) self + 0x60);
}
