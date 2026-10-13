/* func_02019c20 @ 0x02019c20, 0x4a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02019c20_2 {
    int unk_00;
    char pad_04[0x18];
    unsigned short unk_1C;
    unsigned short unk_1E;
    unsigned char unk_20;
} UnkStruct_02019c20_2;

typedef struct UnkStruct_02019c20 {
    char pad_00[0x28];
    int unk_28;
    UnkStruct_02019c20_2 sub;
} UnkStruct_02019c20;

extern void func_02019d70(UnkStruct_02019c20 *s, int a, int b);
extern void func_02019ea0(UnkStruct_02019c20_2 *sub);

int func_02019c20(UnkStruct_02019c20 *s, int x, int v, char c, unsigned short a, unsigned short b)
{
    int result = 0;
    if (x >= s->unk_28 || s->unk_28 == 3) {
        UnkStruct_02019c20_2 *sub = &s->sub;
        func_02019d70(s, 12, x);
        func_02019ea0(sub);
        s->sub.unk_00 = v;
        sub->unk_20 = (unsigned char) c;
        sub->unk_1C = a;
        sub->unk_1E = b;
        result = 1;
    }
    return result;
}
