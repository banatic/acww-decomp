/* func_ov003_0221f3f0 @ 0x0221f3f0, 0x32 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221f5ac(int unused0);
extern int func_02055f1c(int);

int func_ov003_0221f3f0(int param)
{
    int r4;
    int r0;
    int r1;

    r4 = param;
    if (func_ov003_0221f5ac(param) != 0) {
        func_02055f1c(r4);
        r0 = 0;
        r1 = ~r0;
        r0 = r4 + 0xb0;
        *(int *) r0 = r1;
        r0 = r4 + 0xb0;
        r0 = *(int *) r0;
        r4 = r4 + 0xac;
        *(int *) r4 = r0;
        return 1;
    } else {
        return 0;
    }
}
