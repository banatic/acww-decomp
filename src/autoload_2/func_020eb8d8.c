/* func_020eb8d8 @ 0x020eb8d8, 0x54 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int func_ov066_0226760c(void *p);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern int func_ov066_022682ec(void *p, int a, int b);
extern unsigned char data_021fc040[0xe0];

int func_020eb8d8(void *p)
{
    if (func_ov066_0226760c(p) == 7 && p != 0) {
        MI_CpuCopy8(p, data_021fc040, 0xe0);
        return func_ov066_022682ec(data_021fc040, 0, 0);
    }
    return 0;
}
