/* func_ov122_022a1998 @ 0x022a1998, 0x6a bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *, int);
extern void func_020027f0(int);
extern void func_ov002_022080a0(void *, int);
extern void func_ov002_02207e80(void *, int, int, int);
extern int func_ov002_02207f60(void *);

struct UnkStruct_022a1998 {
    char pad_00[0x94];
    int unk_94;
    int unk_98;
};

void func_ov122_022a1998(struct UnkStruct_022a1998 *param)
{
    if (func_ov002_02207f3c(param, 0)) {
        func_020027f0(6);
        func_020027f0(4);
        func_020027f0(3);
        func_ov002_022080a0(param, 5);
    } else {
        func_ov002_02207e80(param, 6, 0, 0);
        func_ov002_02207e80(param, 4, 0, 0);
        func_ov002_02207e80(param, 3, 0, 0);
        param->unk_94 = func_ov002_02207f60(param);
        param->unk_98 = param->unk_94;
    }
}
