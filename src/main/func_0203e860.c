/* func_0203e860 @ 0x0203e860, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203ef90(int arg);
extern int func_02095f28(int arg);
extern int func_02095f08(int arg);

struct UnkStruct_0203e860 {
    unsigned char pad_00[0xC];
    int unk_0C;
    unsigned char pad_10[7];
    unsigned char unk_17;
};

extern int func_0203eb08(struct UnkStruct_0203e860 *arg);

int func_0203e860(struct UnkStruct_0203e860 *arg)
{
    int result1;

    result1 = func_0203ef90(arg->unk_0C);
    if (result1 == 0) {
        return 0;
    }
    if (func_02095f28(result1) == 0) {
        return 0;
    }
    if (func_02095f08(1) == 0) {
        return 0;
    }
    arg->unk_17 = 1;
    return func_0203eb08(arg);
}
