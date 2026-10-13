/* func_02019bd0 @ 0x02019bd0, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02019d70(void *, int, int);
extern void func_02019ea0(void *);

typedef struct UnkStruct_02019bd0_2 {
    char pad_00[0x22];
    unsigned short unk_22;
    int unk_24;
    int unk_28;
    unsigned char unk_2C;
    char pad_2D[3];
    int unk_30;
} UnkStruct_02019bd0_2;

typedef struct {
    char pad_00[0x28];
    int unk_28;
    UnkStruct_02019bd0_2 sub;
} UnkStruct_02019bd0;

int func_02019bd0(UnkStruct_02019bd0 *s, int value, unsigned short *src, int a, unsigned char b, int c, int d)
{
    int result = 0;
    if (value >= s->unk_28 || s->unk_28 == 3) {
        UnkStruct_02019bd0_2 *sub = &s->sub;
        func_02019d70(s, 13, value);
        func_02019ea0(sub);
        sub->unk_22 = *src;
        sub->unk_24 = a;
        sub->unk_2C = b;
        sub->unk_30 = c;
        sub->unk_28 = d;
        result = 1;
    }
    return result;
}
