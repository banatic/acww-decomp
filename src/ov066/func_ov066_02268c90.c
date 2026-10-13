/* func_ov066_02268c90 @ 0x02268c90, 0x78 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern void func_ov066_0226853c(void);

typedef struct {
    int bit0 : 1;
    int bit1 : 1;
    int bit2 : 1;
    int bit3 : 1;
    int : 28;
} Flags;

typedef struct {
    unsigned char pad_00[0xc0];
    Flags flags;
} UnkStruct_02268c90;

extern UnkStruct_02268c90 *data_ov066_0226bdf4;

int func_ov066_02268c90(void)
{
    if (data_ov066_0226bdf4->flags.bit2 && !data_ov066_0226bdf4->flags.bit3) {
        func_ov066_0226853c();
        data_ov066_0226bdf4->flags.bit3 = 1;
        data_ov066_0226bdf4->flags.bit2 = 0;
        return 1;
    }
    return 0;
}
