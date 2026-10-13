/* func_ov122_022a1e90 @ 0x022a1e90, 0x62 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206f58c(void);
extern int func_0206f56c(void);
extern void func_ov122_022a1e00(void *);

int func_ov122_022a1e90(void *param)
{
    func_0206f58c();
    if (func_0206f56c() == 0) {
        goto fail;
    }
    switch (*(unsigned char *) ((char *) param + 0x8d)) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 6:
        case 9:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
            func_ov122_022a1e00(param);
            return 1;
        default:
            goto fail;
    }
fail:
    return 0;
}
