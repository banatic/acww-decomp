/* func_020f4ba8 @ 0x020f4ba8, 0x40 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[8];
    unsigned short unk_08;
    unsigned char unk_0A;
} UnkStruct_020f4ba8;

void func_020f4ba8(UnkStruct_020f4ba8 *p, unsigned short value)
{
    if (p->unk_08 != value) {
        p->unk_0A |= 4;
    } else {
        p->unk_0A &= ~4;
    }
    p->unk_08 = value;
    p->unk_0A &= ~2;
    p->unk_0A |= 1;
}
