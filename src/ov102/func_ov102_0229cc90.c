/* func_ov102_0229cc90 @ 0x0229cc90, 0x78 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229cc90 {
    char pad_00[0xcc];
    int sub;
    char pad_D0[0x259c - 0xd0];
    unsigned short unk_259C;
    unsigned char unk_259E;
    unsigned char unk_259F;
} UnkStruct_0229cc90;

extern int func_ov102_0229d464(void *a, void *b);
extern int func_ov102_0229d454(void *a, void *b);
extern int func_ov102_0229d400(void *a, void *b);
extern int func_ov094_0229aaac(void *sub, int x);
extern int func_ov094_0229aa84(void *sub, int x);
extern void func_ov094_0229aa58(void *sub, int x);
extern void func_ov094_0229a99c(void *sub, int arg2, int arg3);

void func_ov102_0229cc90(UnkStruct_0229cc90 *a, void *b)
{
    int x;
    if (func_ov102_0229d464(a, b) != 0 || func_ov102_0229d454(a, b) != 0) {
        x = func_ov102_0229d400(a, b);
        a->unk_259F = 1;
        a->unk_259C = func_ov094_0229aaac(&a->sub, x);
        a->unk_259E = func_ov094_0229aa84(&a->sub, x);
        func_ov094_0229aa58(&a->sub, x);
        func_ov094_0229a99c(&a->sub, a->unk_259C, a->unk_259E);
    }
}
