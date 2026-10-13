/* func_020422a0 @ 0x020422a0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_020422a0 {
    char pad_00[0x20];
    unsigned int unk_20;
} data_021c779c;
extern unsigned int data_021fbe94;
extern void func_020422d0(unsigned int param);
extern void func_020e993c(unsigned int a, unsigned int b);

void func_020422a0(void)
{
    unsigned int value = data_021c779c.unk_20;
    if (value == 0) {
        return;
    }
    func_020422d0(value);
    func_020e993c(data_021fbe94, value);
    data_021c779c.unk_20 = 0;
}
