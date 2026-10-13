/* func_ov122_022a024c @ 0x022a024c, 0x54 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40[];
extern int func_ov095_02299a00(void *arg);
extern int func_ov095_0229c448(void *arg, int val, int mode);
extern int func_ov095_0229c8e4(void *arg, int val);
extern void func_ov122_0229f194(void *arg);

int func_ov122_022a024c(void *p)
{
    if (!(data_021fbe40[1] & 1)) {
        return 0;
    } else {
        int result = func_ov095_02299a00((char *) p + 0xC0);
        if (result == -1) {
            return 0;
        }
        func_ov095_0229c448((char *) p + 0xC0, result, 9);
        func_ov095_0229c8e4((char *) p + 0xC0, result);
        func_ov122_0229f194(p);
        return 1;
    }
}
