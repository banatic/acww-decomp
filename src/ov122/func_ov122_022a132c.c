/* func_ov122_022a132c @ 0x022a132c, 0x54 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern void func_ov002_02208098(void *ptr, int zero);
extern int func_ov095_0229bf0c(void *ptr);
extern int func_ov095_0229c548(void *ptr);
extern int func_ov095_0229c448(void *ptr, int val, int n);
extern void func_ov122_022a0be4(void *ptr, int val);
extern void func_ov095_0229c8e4(void *ptr, int val);

void func_ov122_022a132c(void *param)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098(param, 0);
        return;
    }
    if (func_ov095_0229bf0c((char *) param + 0xc0) != 0) {
        int v = func_ov095_0229c548((char *) param + 0xc0);
        int w = func_ov095_0229c448((char *) param + 0xc0, v, 9);
        func_ov122_022a0be4(param, w);
        param = (char *) param + 0xc0;
        func_ov095_0229c8e4(param, v);
    }
}
