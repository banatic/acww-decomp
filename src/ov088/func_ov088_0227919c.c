/* func_ov088_0227919c @ 0x0227919c, 0x1c bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov088_02279640(void);
extern int func_ov088_02279784(int, int);

int func_ov088_0227919c(int param)
{
    int r4 = param;
    if (func_ov088_02279640() != 0) {
        func_ov088_02279784(r4, 2);
    }
    return 1;
}
