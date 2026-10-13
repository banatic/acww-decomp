/* func_02074e64 @ 0x02074e64, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern unsigned int func_02073744(unsigned int);
extern unsigned int func_02073768(unsigned int);
extern void func_02077a34(unsigned char *, unsigned char *, unsigned char *);
extern unsigned int func_02077868(unsigned char *);
extern void func_020b65c4(unsigned int);
extern unsigned int func_020a70ec(int, unsigned int, unsigned int, unsigned char *);
extern unsigned int func_02073690(unsigned int);
extern unsigned int func_020736b4(unsigned int);
extern void func_02073698(unsigned int, unsigned int);
extern void *MI_CpuCopy8(void *dest, const void *src, unsigned int n);
int func_02074e64(unsigned char *a, int b)
{
    unsigned int loop_limit;
    int val;
    unsigned int byte_c;
    int val2;
    unsigned int var_10;
    unsigned int result1;
    unsigned char local[8];
    unsigned char *r5;
    unsigned int r6;
    unsigned int r7;
    unsigned int r4;
    r7 = 0;
    var_10 = data_020ccf94;
    loop_limit = func_02073744(var_10);
    r5 = (unsigned char *) func_02073768(var_10);
    r6 = r7;
    while (r6 < loop_limit) {
        MI_CpuCopy8(r5, &local[3], 5);
        byte_c = local[6];
        func_02077a34(&local[7], local, &local[1]);
        r4 = func_02077868(&local[3]);
        func_020b65c4(r4);
        {
            unsigned int res = func_020a70ec(b, byte_c, local[5 * 0], &local[2]);
            if (local[2] != 0) {
                result1 = func_02073690(var_10);
                val = func_020736b4(var_10);
                val = val + result1;
                {
                    unsigned int sum = val;
                    MI_CpuCopy8(r5, (void *) sum, r4 + 5);
                }
                val2 = r4 + 5;
                val2 = result1 + val2;
                func_02073698(var_10, val2);
            } else if (res == b) {
                MI_CpuCopy8(r5, a, r4 + 5);
                a += r4 + 5;
                r7 += r4 + 5;
            }
        }
        r5 += r4 + 5;
        r6 += r4 + 5;
    }

    return r7;
}
