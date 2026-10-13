/* func_ov009_0226303c @ 0x0226303c, 0x20 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov009_0226305c(void *param);

struct func_ov009_0226303c_obj {
    char pad_00[0x27c];
    int flag;
};

int func_ov009_0226303c(struct func_ov009_0226303c_obj *param)
{
    if (param->flag == 0) {
        return func_ov009_0226305c(param);
    } else {
        return 0;
    }
}
