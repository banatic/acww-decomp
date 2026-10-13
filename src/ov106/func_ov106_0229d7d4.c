/* func_ov106_0229d7d4 @ 0x0229d7d4, 0x3c bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov106_0229cd60(int, unsigned char);
extern int func_ov106_0229cde4(int);
extern int func_ov002_02209d8c(int);
extern int func_ov002_02208098(int, int);
extern int func_ov094_022999d8(void);

void func_ov106_0229d7d4(int param)
{
    if (func_ov002_02209d8c(param + 0x2288) != 0) {
        func_ov106_0229cd60(param, *(unsigned char *) (param + 0xb7));
        func_ov002_02208098(param, 0x24);
        func_ov094_022999d8();
    } else {
        func_ov106_0229cde4(param);
    }
}
