/* func_020c0c1c @ 0x020c0c1c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct Global {
    char pad_00[0x28];
    int unk_28;
} data_021f8ab0;

extern struct Param {
    char pad_00[0x6c];
    int unk_6C;
};

extern void func_020e88dc(int *p, int a, int b);

void func_020c0c1c(struct Param *param)
{
    int arg1;
    int local;

    if (data_021f8ab0.unk_28 != 3 && data_021f8ab0.unk_28 != 4) {
        arg1 = 0x1000;
    } else {
        arg1 = 0;
    }

    local = param->unk_6C;
    func_020e88dc(&local, arg1, 0x100);
    param->unk_6C = local;
}
