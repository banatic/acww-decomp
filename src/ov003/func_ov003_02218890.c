/* func_ov003_02218890 @ 0x02218890, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02077978(void);
extern int func_020778f8(int);

void func_ov003_02218890(int a1, int a2, int a3, short *a4)
{
    int r5 = a1;
    short *r4 = a4;
    func_02077978();
    *r4 = (short) func_020778f8(r5 + 5);
}
