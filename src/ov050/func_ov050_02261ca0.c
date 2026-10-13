/* func_ov050_02261ca0 @ 0x02261ca0, 0x14 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201b3a4(int, int);

struct UnkStruct_02261ca0 {
    char pad_00[0xb4];
    int unk_B4;
    char pad_B8[0x0c];
    int unk_C4;
};

int func_ov050_02261ca0(struct UnkStruct_02261ca0 *p)
{
    return func_0201b3a4(p->unk_B4, p->unk_C4);
}
