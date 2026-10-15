/* func_020eb92c @ 0x020eb92c, 0x6c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *dst, int data, unsigned long size);
extern int func_ov066_02267784(int a, unsigned char b);
extern int func_ov066_02266c7c(void *argument0);
extern int func_ov066_0226760c(void);
extern int data_021fbf78[8];

int *func_020eb92c(void)
{
    MI_CpuFill8(data_021fbf78, 0, 0x20);
    if (func_ov066_0226760c() == 7) {
        unsigned int i = 0;
        int idx = 0;
        do {
            int val = func_ov066_02267784(0, i);
            if (func_ov066_02266c7c((void *) val) != 0) {
                data_021fbf78[idx] = val;
                idx++;
            }
            i++;
        } while (i < 8);
    }
    return data_021fbf78;
}
