/* func_020b5be4 @ 0x020b5be4, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d068(void *);
extern void func_020a53ec(int, int, int, int);

struct UnkStruct_020b5be4 {
    char pad_00[0x50];
    int unk_50;
};

void func_020b5be4(struct UnkStruct_020b5be4 *param)
{
    int result;
    result = func_0209d068(param);
    func_020a53ec(6, 3, result, 1);
    param->unk_50 = 2;
}
