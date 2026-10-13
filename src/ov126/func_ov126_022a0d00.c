/* func_ov126_022a0d00 @ 0x022a0d00, 0x30 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

struct SParameter {
    unsigned char pad_00[0xae];
    unsigned char unk_AE;
};

extern unsigned short data_021fbe40;
extern void func_ov002_02208098(struct SParameter *param, unsigned char val);
extern void func_ov126_022a0978(struct SParameter *param);

void func_ov126_022a0d00(struct SParameter *param)
{
    if ((data_021fbe40 & 0x200) != 0) {
        return;
    }
    func_ov002_02208098(param, param->unk_AE);
    func_ov126_022a0978(param);
}
