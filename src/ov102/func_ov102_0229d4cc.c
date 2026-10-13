/* func_ov102_0229d4cc @ 0x0229d4cc, 0x3c bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x24e0];
    int unk_24E0;
    int unk_24E4;
} UnkStruct_0229d4cc;

extern int func_ov102_0229cc90(UnkStruct_0229d4cc *, int, int);
extern int func_ov102_0229d1e8(UnkStruct_0229d4cc *, int);
extern int func_ov102_0229d178(UnkStruct_0229d4cc *, int);
extern int func_ov102_0229d54c(UnkStruct_0229d4cc *, int, int);

void func_ov102_0229d4cc(UnkStruct_0229d4cc *a, int b, int c)
{
    func_ov102_0229cc90(a, b, c);
    a->unk_24E0 = func_ov102_0229d1e8(a, b);
    a->unk_24E4 = func_ov102_0229d178(a, b);
    func_ov102_0229d54c(a, c, 4);
}
