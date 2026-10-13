/* func_020ba0cc @ 0x020ba0cc, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xc];
    unsigned int unk_0C;
    unsigned int unk_10;
} UnkStruct_020ba0cc;

unsigned int func_020ba0cc(UnkStruct_020ba0cc *p)
{
    return ((p->unk_10 - p->unk_0C + 0x3f) << 18) >> 24;
}
