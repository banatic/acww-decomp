/* func_0202d060 @ 0x0202d060, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020617d8(int);
extern void MI_CpuCopy8(void *, void *, int);
extern void func_0202d3d4(int *, int *);
extern int func_0202d6e4(void *, int);
extern int func_0202d1a8(int, int, int, int, int, int *, int);
extern int data_020c8948;
extern unsigned char data_021c1d10[];

int func_0202d060(int a, int *b, int c, int d, unsigned char *e)
{
    int res;
    int varA;
    int varB;
    int i;
    int r4;
    int ok;
    int buffer[4];
    int result = 0;

    res = func_020617d8(e[4] - 1);
    if (res != 0) {
        varB = 0;
        MI_CpuCopy8(&data_020c8948, data_021c1d10, 5);
        func_0202d3d4(buffer, &varB);

        i = 0;
        varA = i;
        while (i < 5) {
            r4 = func_0202d6e4(data_021c1d10, 5);
            if (r4 < 0 || r4 >= 5) {
                break;
            }
            ok = func_0202d1a8(a, c, d, r4, res, buffer, varB);
            if (ok == 1) {
                *b = r4;
                result = 1;
                break;
            } else {
                data_021c1d10[r4] = varA;
                i++;
            }
        }
    }
    return result;
}
