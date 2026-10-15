/* func_ov066_02266824 @ 0x02266824, 0x48 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern struct UnkStruct_02266824 *data_ov066_0226bdec;

struct UnkStruct_02266824 {
    char pad_00[0x38];
    void (*func)(unsigned char *);
};

void func_ov066_02266824(unsigned char *p)
{
    struct UnkStruct_02266824 *ptr = data_ov066_0226bdec;
    if (ptr == 0) {
        return;
    }
    if (ptr->func == 0) {
        return;
    }
    ptr->func(p);
}
