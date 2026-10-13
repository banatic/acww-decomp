/* func_02057468 @ 0x02057468, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020574a0(void);
extern int func_02057a50(int, int);
extern int func_02057430(int, int);

int func_02057468(int arg0, int arg1, int arg2)
{
    int r0;
    int r1;
    int r2;
    int r4;
    int r5;
    int r6;

    r5 = arg0;
    r4 = arg1;
    r6 = arg2;
    r0 = func_020574a0();
    if (r0 == 0) {
        r0 = func_02057a50(r4, r6);
        r2 = (r0 << 0x18) >> 0x18;
        r0 = 0;
        r1 = ~r0;
        if (r2 != r1) {
            r0 = func_02057430(r5, r4);
        } else {
            r0 = 0;
        }
    } else {
        r0 = 0;
    }
    return r0;
}
