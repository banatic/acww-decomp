/* func_ov136_0229c684 @ 0x0229c684, 0x60 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x8D];
    unsigned char unk_8D;
    char pad_8E[0x94 - 0x8D - 1];
    char unk_94;
    char pad_95[0x2B76 - 0x94 - 1];
    unsigned char unk_2B76;
} UnkStruct_0229c684;

extern int func_ov136_0229c574(void *, int);
extern void func_ov002_0220a05c(void *, void *, void *, int, int);
extern void func_ov002_02208098(void *, int);
extern int func_ov136_0229c554(void *, int);

int func_ov136_0229c684(UnkStruct_0229c684 *arg0, void *arg1, void *arg2)
{
    if (func_ov136_0229c574(arg0, 4)) {
        func_ov002_0220a05c(&arg0->unk_94, arg1, arg2, 2, 1);
    } else {
        func_ov002_0220a05c(&arg0->unk_94, arg1, arg2, 3, 1);
    }
    arg0->unk_2B76 = arg0->unk_8D;
    func_ov002_02208098(arg0, 0xa);
    return func_ov136_0229c554(arg0, 4);
}
