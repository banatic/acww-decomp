/* func_0204beb0 @ 0x0204beb0, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_02062130(unsigned int param0, unsigned int param1);
extern unsigned int func_0204bf20(unsigned int param0);
extern unsigned int NNS_FndAllocFromAllocator(unsigned int *param0, unsigned int param1);
extern int func_0204bd84(unsigned int *param0);
extern void func_0204bf18(unsigned int *param0, unsigned int *param1);
extern unsigned int func_020051b0(unsigned int *param0);

unsigned int func_0204beb0(unsigned int *param0, unsigned int param1)
{
    unsigned int local;
    unsigned int r4;
    unsigned int r6;

    param1 = param1 < func_02062130((unsigned int) param0, param1) ? param1 : 0;
    r6 = 0;
    for (r4 = r6; r4 < 0x21; r4++) {
        NNS_FndAllocFromAllocator(&local, func_0204bf20(r4));
        if (func_0204bd84(&local)) {
            if (param1 == r6) {
                func_0204bf18(param0, &local);
                return func_020051b0(&local);
            }
            r6++;
        }
        func_020051b0(&local);
    }
    return NNS_FndAllocFromAllocator(param0, func_0204bf20(0));
}
