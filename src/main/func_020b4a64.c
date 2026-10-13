/* func_020b4a64 @ 0x020b4a64, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b4a64(void *self);

int func_020b4a64(void *self)
{
    if (*(int *) ((char *) self + 0x28) > 0) {
        return 1;
    }
    return 0;
}
