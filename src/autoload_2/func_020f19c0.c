/* func_020f19c0 @ 0x020f19c0, 0x94 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f0ddc(void *something, int param);
extern void func_020f0d98(void *something, int param1, int param2);

struct UnkStruct_020f19c0 {
    unsigned int pad_00;
    unsigned char something[4];
    unsigned char pad_08[92];
    unsigned short unk_64;
};

void func_020f19c0(struct UnkStruct_020f19c0 *a, unsigned int b)
{
    func_020f0ddc(&a->something[0], 0);
    switch (b) {
        case 0:
            break;
        case 1:
            a->unk_64 = 0x84;
            break;
        case 2:
            a->unk_64 = 0x18;
            break;
        case 3:
            a->unk_64 = 0x1800;
            break;
        case 4:
            a->unk_64 = 0x700;
            break;
        case 5:
            a->unk_64 = 0x63;
            break;
        default:
            break;
    }
    func_020f0d98(&a->something[0], 0x7f, 0xf);
}
