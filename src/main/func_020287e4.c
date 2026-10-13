/* func_020287e4 @ 0x020287e4, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02137550(void *, int);
extern int func_0208150c(int);
extern int func_0207cb9c(int *, int *, int);
extern void func_02015e10(void *, int, int);
extern int data_021e5a2c;

struct UnkStruct_020287e4 {
    char pad_00[0x830];
    int unk_830;
};

struct UnkStruct_020287e4_2 {
    char pad_00[0x100];
    struct UnkStruct_020287e4 *sub;
    char pad_104[0x58];
    int unk_15C;
};

void func_020287e4(struct UnkStruct_020287e4_2 *obj)
{
    int local;
    func_02137550(&local, 4);
    local = func_0208150c(obj->sub->unk_830);
    obj->unk_15C = func_0208150c(func_0207cb9c(&data_021e5a2c, &local, 1));
    func_02015e10(obj, obj->unk_15C, 1);
}
