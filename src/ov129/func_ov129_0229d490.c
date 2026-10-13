/* func_ov129_0229d490 @ 0x0229d490, 0x26 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xa0];
    int unk_A0;
} UnkStruct_0229d490;

extern int func_ov002_02207f3c(UnkStruct_0229d490 *s, int n);
extern int func_ov002_02207f60(UnkStruct_0229d490 *s);
extern void func_ov129_0229d440(UnkStruct_0229d490 *s);

void func_ov129_0229d490(UnkStruct_0229d490 *s)
{
    if (func_ov002_02207f3c(s, -1) != 0) {
        func_ov129_0229d440(s);
    }
    s->unk_A0 = func_ov002_02207f60(s);
}
