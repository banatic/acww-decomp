/* func_02078cb0 @ 0x02078cb0, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern unsigned char data_020e54a8;
extern int data_021c9ac4;
extern int func_02082240(void);
extern unsigned char func_020b65c4(void);
extern int func_020b5df8(unsigned int);
extern int func_020b5e04(unsigned int);
extern int func_02085f08(void);
extern int func_020e9968(int, int, int);

void func_02078cb0(int *out)
{
    int base;
    int cond;
    int limit_part;
    int limit;
    int i;
    int tmp1, tmp2;

    base = data_021c9ac4;
    cond = (data_020e54a8 == 0) ? 1 : 0;
    if (cond != 0) {
        limit_part = func_02082240();
    } else {
        tmp1 = func_020b5df8((unsigned int) func_020b65c4());
        tmp2 = func_020b5e04((unsigned int) func_020b65c4());
        limit_part = tmp1 - tmp2;
    }

    limit = limit_part + func_02085f08();

    for (i = 0; i < limit; i++) {
        out[i] = func_020e9968(base, 0x2f88, 4);
    }
}
