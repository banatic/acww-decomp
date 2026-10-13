/* func_ov129_0229d554 @ 0x0229d554, 0x32 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x9c];
    int unk_9C;
    int unk_A0;
} UnkStruct_0229d554;

extern int func_ov002_02207f3c(UnkStruct_0229d554 *, int);
extern int func_ov002_02207f60(UnkStruct_0229d554 *);
extern void func_ov129_0229d500(UnkStruct_0229d554 *);

void func_ov129_0229d554(UnkStruct_0229d554 *arg)
{
    if (func_ov002_02207f3c(arg, -1)) {
        func_ov129_0229d500(arg);
    }
    arg->unk_A0 = func_ov002_02207f60(arg);
    arg->unk_9C = func_ov002_02207f60(arg);
}
