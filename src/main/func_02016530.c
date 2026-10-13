/* func_02016530 @ 0x02016530, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020165bc(int a, int b, int c, int d);
extern void func_02054240(int a, int b, int c, int d, int e, int f, int g, int h);
extern int func_0205cebc(int a);
extern int func_0205cf10(int a);
extern int func_0205ceec(int a, int b);
extern int func_0205cec8(int a, int b);
extern void func_020541b8(int a, int b, int c);
extern void func_02016520(int a, int b);

void func_02016530(int param1, int param2, int param3, int param4)
{
    int result;
    int r7;
    int count;
    unsigned int i;
    int tmp;
    int tmp2;

    result = func_020165bc(param1, param2, param3, param4);
    if (result != 0) {
        func_02054240(param2 + 0xec, result, 0, 1, 0x1000, param3, param4, 0);
        r7 = func_0205cebc(0x143);
        if (r7 < 4) {
            count = func_0205cf10(r7);
            for (i = 0; i < (unsigned int) count; i++) {
                tmp = func_0205ceec(r7, i);
                tmp2 = func_0205cec8(r7, i);
                func_020541b8(param2 + 0xec, tmp, tmp2);
            }
        } else {
            func_02016520(param1, param2);
        }
    } else {
        func_02016520(param1, param2);
    }
}
