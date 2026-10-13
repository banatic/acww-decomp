/* func_ov066_022693f0 @ 0x022693f0, 0x4c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    unsigned char pad_00[0xc0];
    unsigned int bit0 : 1;
    int bit1 : 1;
} UnkStruct_022693f0;

extern UnkStruct_022693f0 *data_ov066_0226bdf4;
extern void func_ov066_0226943c(void);

void func_ov066_022693f0(void)
{
    data_ov066_0226bdf4->bit0 = 0;
    if (data_ov066_0226bdf4->bit1 == 0) {
        return;
    }
    func_ov066_0226943c();
}
