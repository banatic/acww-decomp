/* func_ov047_02262390 @ 0x02262390, 0x3c bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern int func_02019d0c(char *a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);

int func_ov047_02262390(char *p)
{
    int v0 = 0;
    int v1 = 0;
    int v2 = *(signed short *) (p + 0x734);
    int v3 = 0;
    int v4 = 0;
    int v5 = data_020c80f8;
    int v6 = 0;
    func_02019d0c(p + 0x564, 3, 1, 0, v0, v1, v2, v3, v4, v5, v6);
    return 1;
}
