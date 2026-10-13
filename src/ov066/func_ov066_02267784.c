/* func_ov066_02267784 @ 0x02267784, 0x5c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

struct ListStruct {
    int unk_00;
    int unk_04;
    char *entries;
};

extern struct ListStruct *data_ov066_0226bdf0;
extern unsigned char *data_ov066_0226bdec;
extern int func_ov066_0226a418(void *ptr, int arg);

int func_ov066_02267784(unsigned int idx, int arg)
{
    if (data_ov066_0226bdf0 != 0 && idx < data_ov066_0226bdec[9]) {
        return func_ov066_0226a418((char *) data_ov066_0226bdf0->entries + (idx << 4), arg);
    }
    return 0;
}
