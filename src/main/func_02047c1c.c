/* func_02047c1c @ 0x02047c1c, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02047dd4(int, int, int, int, int, int, int);
extern void func_02047c98(int, int, int, int);

extern char data_021c7a08[];

void func_02047c1c(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
    int n = func_02047dd4(a0, 16, a2, a5, a6, a7, a8);
    int r5, r4;

    while (n != 0) {
        for (r4 = 0; r4 < a4; r4++) {
            int off = r4;
            off *= 36;
            for (r5 = 0; r5 < a3; r5++) {
                if (((int) (*(int *) ((char *) data_021c7a08 + r5 * 144 + off + 0x20)) << 20) >> 31) {
                    func_02047c98(a0, a1, r5, r4);
                }
            }
        }
        n--;
    }
}
