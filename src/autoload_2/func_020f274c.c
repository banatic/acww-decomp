/* func_020f274c @ 0x020f274c, 0x38 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f6700(int, void *);
extern void func_020f43f8(int, int, void *, int);

struct UnkStruct_020f274c {
    char pad_00[0x30];
    int unk_30;
    char pad_34[0x19];
    char unk_4D;
};
extern struct UnkStruct_020f274c data_021fd1bc;

void func_020f274c(int arg)
{
    func_020f6700(data_021fd1bc.unk_30, &data_021fd1bc);
    data_021fd1bc.unk_4D = 1;
    func_020f43f8(arg, 0x11, &data_021fd1bc, 1);
}
