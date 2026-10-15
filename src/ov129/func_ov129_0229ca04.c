/* func_ov129_0229ca04 @ 0x0229ca04, 0x6c bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;

extern int func_ov002_02208054(void *p, int a);
extern int func_ov002_0220a784(void *p, int a);
extern unsigned char *func_ov129_0229d380(void *p);
extern void func_ov129_0229c684(void *p);
extern void func_ov129_0229c644(void *p);

void func_ov129_0229ca04(void *param)
{
    unsigned int flag;

    if (func_ov002_02208054(param, 1)) {
        func_ov129_0229d380(param);
        return;
    }

    flag = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (flag != 0) {
        if (func_ov002_0220a784((char *) param + 0x1d4, 3)) {
            func_ov129_0229c684(param);
            return;
        }
        if (func_ov002_0220a784((char *) param + 0x1d4, 4)) {
            func_ov129_0229c644(param);
            return;
        }
    }
}
