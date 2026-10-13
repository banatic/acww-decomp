/* func_020940d0 @ 0x020940d0, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x39c];
    unsigned short unk_39C;
} Cfg;

extern Cfg data_021d52d8;
extern int data_021d5658;
extern int data_020e28f4;

extern int func_02094cf8(int kind, int a0, int a1, int a2, int a3, int zero);
extern void func_02091494(void *ctx, int hw, int a0, int a1, int a2, int a3, int minus1);
extern int func_02090ac4(int kind, int a1, int a2, void *tbl);
extern void func_020914dc(void *ctx);

int func_020940d0(int a0, int a1, int a2, int a3)
{
    int ret;
    Cfg *cfg;

    cfg = &data_021d52d8;
    ret = 3;
    if (func_02094cf8(0x37, a0, a1, a2, a3, 0) < 3) {
        func_02091494(&data_021d5658, cfg->unk_39C, a0, a1, a2, a3, -1);
        if (func_02090ac4(0x5e, a1, a2, &data_020e28f4) != 0) {
            ret = 2;
        }
    }
    func_020914dc(&data_021d5658);
    return ret;
}
