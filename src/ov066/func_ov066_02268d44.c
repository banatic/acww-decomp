/* func_ov066_02268d44 @ 0x02268d44, 0x60 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(void *dst, const void *src, unsigned int n);
extern void func_ov066_02269320(void *a, void *b);
extern void func_ov066_022692c0(void);
extern void func_ov066_02266bf4(void);
extern char *data_ov066_0226bdf4;
extern int *data_ov066_0226bdec;

void func_ov066_02268d44(void *arg)
{
    char local[8];
    MI_CpuCopy8(arg, &local, 8);
    func_ov066_02269320(data_ov066_0226bdf4 + 0x28, (char *) arg + 8);
    func_ov066_022692c0();
    if (data_ov066_0226bdec[1] == 9) {
        data_ov066_0226bdec[1] = 0xb;
    }
    func_ov066_02266bf4();
}
