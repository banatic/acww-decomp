/* func_020b0ae0 @ 0x020b0ae0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202f134(int, void *, unsigned short, int);
extern void *data_021f42f4;

struct UnkParam {
    unsigned char pad_00[6];
    unsigned short unk_06;
};

void func_020b0ae0(struct UnkParam *param)
{
    func_0202f134(0xc, data_021f42f4, param->unk_06, 0);
}
