/* func_0207acbc @ 0x0207acbc, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0207acbc {
    char pad_00[0x64];
    int unk_64;
};

extern struct UnkStruct_0207acbc *data_020ccf94;
extern int func_02073d90(struct UnkStruct_0207acbc *);
extern int func_02073dd4(struct UnkStruct_0207acbc *, int);
extern void func_0207acf8(int, int);
extern void func_0207ae34(int);

void func_0207acbc(int a, int b)
{
    if (func_02073d90(data_020ccf94) == 0) {
        func_0207acf8(a, b);
    }
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0) {
        func_0207ae34(a);
    }
}
