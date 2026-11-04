/* network_7: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020eb8d8 @ 0x020eb8d8, 0x54 bytes, ARM
 * func_020eb8a0 @ 0x020eb8a0, 0x38 bytes, ARM
 * func_020eb868 @ 0x020eb868, 0x38 bytes, ARM
 */

extern int func_ov066_0226760c(void);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern int func_ov066_022682ec(void *p, int a, int b);
extern unsigned char data_021fc040[0xe0];
extern unsigned short data_021fbefc;
extern int DWCi_GetFriendListIndex(int a);
extern int DWCi_GetProfileIDFromList(int index);

int func_020eb8d8(void *p)
{
    if (func_ov066_0226760c() == 7 && p != 0) {
        MI_CpuCopy8(p, data_021fc040, 0xe0);
        return func_ov066_022682ec(data_021fc040, 0, 0);
    }
    return 0;
}

int func_020eb8a0(int a)
{
    if (data_021fbefc < 4) {
        return -1;
    }
    return DWCi_GetFriendListIndex(a);
}

int func_020eb868(int a)
{
    unsigned short s = data_021fbefc;
    if (s < 4) {
        return -1;
    }
    return DWCi_GetProfileIDFromList(a);
}
