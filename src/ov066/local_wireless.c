/* local_wireless: 3 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_02266824 @ 0x02266824, 0x48 bytes, ARM
 * func_ov066_02266800 @ 0x02266800, 0x24 bytes, ARM
 * func_ov066_022667e0 @ 0x022667e0, 0x20 bytes, ARM
 */

struct UnkStruct_02266824 {
    char pad_00[0x38];
    void (*func)(unsigned char *);
};

typedef struct {
    unsigned char pad_00[0x38];
    int unk_38;
} UnkStruct_022667e0;

extern struct UnkStruct_02266824 *data_ov066_0226bdec;

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

void func_ov066_02266800(unsigned char a, unsigned char b)
{
    unsigned char buf[2];
    buf[0] = a;
    buf[1] = b;
    func_ov066_02266824(buf);
}

int func_ov066_022667e0(int value)
{
    if ((*(UnkStruct_022667e0 * *) &data_ov066_0226bdec) != 0) {
        (*(UnkStruct_022667e0 * *) &data_ov066_0226bdec)->unk_38 = value;
        return 1;
    } else {
        return 0;
    }
}
