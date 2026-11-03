/* nook_clerk_talk_6: 2 functions, module ov050
 * mwccarm 1.2/base -O4,s
 * func_ov050_02263640 @ 0x02263640, 0x6 bytes, Thumb
 * func_ov050_02263638 @ 0x02263638, 0x6 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[176];
    unsigned long unk_B0;
} UnkStruct_02263640;

typedef struct {
    unsigned char pad_00[176];
    unsigned long unk_B0;
} UnkStruct_02263638;

void func_ov050_02263640(UnkStruct_02263640 *p, unsigned long v)
{
    p->unk_B0 = v;
}

unsigned long func_ov050_02263638(UnkStruct_02263638 *p)
{
    return p->unk_B0;
}
