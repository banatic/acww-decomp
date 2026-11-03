/* scene_motion_request: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02019c20 @ 0x02019c20, 0x4a bytes, Thumb
 * func_02019bd0 @ 0x02019bd0, 0x50 bytes, Thumb
 * func_02019b80 @ 0x02019b80, 0x50 bytes, Thumb
 * func_02019b78 @ 0x02019b78, 0x6 bytes, Thumb
 * func_02019b70 @ 0x02019b70, 0x6 bytes, Thumb
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

typedef struct UnkStruct_02019b80_2 {
    char pad_00[0x22];
    unsigned short unk_22;
    int unk_24;
    int unk_28;
    unsigned char unk_2C;
    char pad_2D[3];
    int unk_30;
} UnkStruct_02019b80_2;

typedef struct {
    char pad_00[0x28];
    int unk_28;
    UnkStruct_02019b80_2 sub;
} UnkStruct_02019b80;

typedef struct {
    unsigned char pad_00[25];
    unsigned char unk_19;
} UnkStruct_02019b78;

typedef struct {
    unsigned char pad_00[25];
    unsigned char unk_19;
} UnkStruct_02019b70;

extern void func_02019d70(void *, int, int);
extern void func_02019ea0(void *);

int func_02019c20(UnkStruct_02019c20 *s, int x, int v, char c, unsigned short a, unsigned short b)
{
    int result = 0;
    if (x >= s->unk_28 || s->unk_28 == 3) {
        UnkStruct_02019c20_2 *sub = &s->sub;
        func_02019d70((void *) s, 12, x);
        func_02019ea0((void *) sub);
        s->sub.unk_00 = v;
        sub->unk_20 = (unsigned char) c;
        sub->unk_1C = a;
        sub->unk_1E = b;
        result = 1;
    }
    return result;
}

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

int func_02019b80(UnkStruct_02019b80 *s, int value, unsigned short *src, int a, unsigned char b, int c, int d)
{
    int result = 0;
    if (value >= s->unk_28 || s->unk_28 == 3) {
        UnkStruct_02019b80_2 *sub = &s->sub;
        func_02019d70(s, 14, value);
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

void func_02019b78(UnkStruct_02019b78 *p)
{
    p->unk_19 = 1;
}

void func_02019b70(UnkStruct_02019b70 *p)
{
    p->unk_19 = 2;
}
