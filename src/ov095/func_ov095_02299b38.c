/* func_ov095_02299b38 @ 0x02299b38, 0x44 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229c52c(void *self, int field);
extern int func_ov095_022999b0(void *self, int arg);

int func_ov095_02299b38(void *self)
{
    if (*(int *) ((char *) self + 0x28) == 0x103) {
        *(int *) ((char *) self + 0x30) = *(int *) ((char *) self + 0x38);
        return *(int *) ((char *) self + 0x30);
    }
    if (func_ov095_0229c52c(self, *(int *) ((char *) self + 0x28)) != -1) {
        return *(int *) ((char *) self + 0x30);
    }
    if (func_ov095_022999b0(self, 4) == 0) {
        return *(int *) ((char *) self + 0x30) - 8;
    }
    return *(int *) ((char *) self + 0x30);
}
