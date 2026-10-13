/* func_ov129_0229d5a4 @ 0x0229d5a4, 0x46 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f60(int);
extern void func_02001b6c(int);
extern void func_02001b7c(int);
extern void func_02002808(int, int, int, int, int);

void func_ov129_0229d5a4(int param)
{
    int a, b;

    a = func_ov002_02207f60(param) - 0x40;
    if (a < 0) {
        a = 0;
    }

    b = func_ov002_02207f60(param) - 0x30;

    if (b <= 0) {
        func_02001b6c(2);
    } else {
        func_02001b7c(2);
        func_02002808(3, 0, a, 0xff, b);
    }
}
