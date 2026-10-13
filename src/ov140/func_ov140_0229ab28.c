/* func_ov140_0229ab28 @ 0x0229ab28, 0x48 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229ab28 {
    unsigned char pad_00[0x8df];
    unsigned char unk_8DF;
} UnkStruct_0229ab28;

extern int func_ov140_0229a244(UnkStruct_0229ab28 *);
extern void func_ov140_0229a078(UnkStruct_0229ab28 *);
extern void func_ov140_0229a280(UnkStruct_0229ab28 *);
extern void func_ov140_0229a164(UnkStruct_0229ab28 *, int);
extern int func_ov140_0229a384(UnkStruct_0229ab28 *);

void func_ov140_0229ab28(UnkStruct_0229ab28 *p)
{
    int x = func_ov140_0229a244(p);

    if (x != p->unk_8DF) {
        p->unk_8DF = x;
        func_ov140_0229a078(p);
        func_ov140_0229a280(p);
        func_ov140_0229a164(p, 5);
    } else if (func_ov140_0229a384(p)) {
        func_ov140_0229a164(p, 5);
    }
}
