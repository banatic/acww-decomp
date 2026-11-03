/* barber_talk_3: 2 functions, module ov053
 * mwccarm 1.2/base -O4,s
 * func_ov053_0226151c @ 0x0226151c, 0x6 bytes, Thumb
 * func_ov053_02261514 @ 0x02261514, 0x6 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[186];
    unsigned char unk_BA;
} UnkStruct_0226151c;

typedef struct {
    unsigned char pad_00[187];
    unsigned char unk_BB;
} UnkStruct_02261514;

unsigned char func_ov053_0226151c(UnkStruct_0226151c *p)
{
    return p->unk_BA;
}

unsigned char func_ov053_02261514(UnkStruct_02261514 *p)
{
    return p->unk_BB;
}
