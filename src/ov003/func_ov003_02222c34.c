/* func_ov003_02222c34 @ 0x02222c34, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02222c34_2 {
    char pad_00[0x2c];
    void *unk_2C;
};

struct UnkStruct_02222c34 {
    unsigned char *unk_00;
    struct UnkStruct_02222c34_2 *unk_04;
    unsigned char pad_08[0xb0];
    int *unk_B8;
};

void func_ov003_02222c34(struct UnkStruct_02222c34 *p)
{
    void *base;
    unsigned int v;
    base = p->unk_04->unk_2C;
    if (p->unk_00[1] == 2) {
        v = *(unsigned int *) ((unsigned char *) base + 0xd4);
        switch (v) {
            case 0:
            case 1:
            case 2:
            case 3:
                *p->unk_B8 = 0;
                break;
        }
    }
}
