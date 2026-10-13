/* func_020172d8 @ 0x020172d8, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020172d8 {
    unsigned char pad_00[0x22];
    unsigned short unk_22;
};

struct UnkStruct_020172d8_2 {
    unsigned char pad_00[0x28];
    int unk_28;
    struct UnkStruct_020172d8 sub;
};

extern void func_02019d70(struct UnkStruct_020172d8_2 *s, int a, int b);
extern void func_02019ea0(struct UnkStruct_020172d8 *s);

int func_020172d8(struct UnkStruct_020172d8_2 *s, int val, unsigned short *src)
{
    int ret = 0;
    if (val >= s->unk_28 || s->unk_28 == 3) {
        struct UnkStruct_020172d8 *sub = &s->sub;
        func_02019d70(s, 0x14, val);
        func_02019ea0(sub);
        sub->unk_22 = *src;
        ret = 1;
    }
    return ret;
}
