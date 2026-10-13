/* func_02098adc @ 0x02098adc, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02098c2c(void *p, int n);
extern unsigned short *func_02098f48(void *p, int n);
extern void func_02098f0c(void *p, unsigned short *ptr, int n, int m);
extern int func_0204c878(unsigned short *ptr);

int func_02098adc(void *p, int n)
{
    int r5 = n;
    unsigned short local[2];

    if (r5 < 0) {
        r5 = 0;
    }
    local[0] = 0xFFF1;
    while (r5 > 0) {
        int ret = func_02098c2c(p, 1);
        if (ret == -1) {
            break;
        }
        local[0] = *func_02098f48(p, ret);
        local[1] = 0xFFF1;
        func_02098f0c(p, &local[1], ret, 0);
        r5 -= func_0204c878(local);
    }
    if (r5 != 0) {
        r5 = -r5;
    }
    return r5;
}
