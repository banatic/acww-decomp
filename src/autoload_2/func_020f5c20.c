/* func_020f5c20 @ 0x020f5c20, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020f5c20 {
    unsigned int unk_00;
    volatile unsigned int unk_04;
    volatile unsigned int unk_08;
    volatile unsigned int unk_0C;
    volatile unsigned int unk_10;
    volatile unsigned int unk_14;
    volatile unsigned int unk_18;
};

void func_020f5c20(struct UnkStruct_020f5c20 *p)
{
    p->unk_10 = 0;
    p->unk_0C = p->unk_10;
    p->unk_08 = p->unk_0C;
    p->unk_04 = p->unk_08;
    p->unk_18 = 0;
    p->unk_14 = p->unk_18;
}
