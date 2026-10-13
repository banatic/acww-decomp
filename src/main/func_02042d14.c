/* func_02042d14 @ 0x02042d14, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0204f5e0(int, int, int, int, int, int);
extern int func_0204ee7c(int, int, int);
extern void func_02046024(int, int *, int, int, int, int, int, int, int, int);
extern unsigned short data_020cab3c[];

int func_02042d14(short *param1, int param2, int *param3)
{
    int res = 0;
    int p0 = param3[0];
    int p1 = param3[1];
    int q0 = p0 >> 4;
    int q1 = p1 >> 4;
    int rem1 = p1 - (q1 << 4);
    int val;
    int rem0 = p0 - (q0 << 4);
    void *r = func_0204f5e0(param2, q0, q1, rem0, rem1, res);
    if ((0 != r) && ((*((unsigned short *) r)) == 0xFFF1)) {
        if (func_0204ee7c(param2, param3[0, 0], param3[1]) != 0) {
            int local[2];
            val = param3[1];
            local[0] = param3[0];
            local[1] = val;
            func_02046024(res, local, data_020cab3c[param1[1]], 0xFFF1, res, res, rem1 = res, 3, res, ~res);
            res = 1;
        }
    }
    return res;
}
