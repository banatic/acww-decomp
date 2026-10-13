/* func_02094294 @ 0x02094294, 0xd0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x34];
    int unk_34;
    unsigned char pad_38[0x40 - 0x38];
} Big;

extern void func_02034270(Big *b, void *v, int c, int d);
extern void func_0203423c(Big *b);
extern int func_020ba4e4(void);
extern int func_020b6598(void);
extern void func_02091494(void *t, int id, void *a, void *b, void *c, void *d, int e);
extern int func_02090ac4(int k, void *b, void *c, void *tbl);
extern int func_02094cf8(int k, void *a, void *b, void *c, void *d, int e);
extern unsigned short data_021d52d8[];
extern void *data_021d5658;
extern unsigned char data_020e289c[];
extern unsigned char data_020e28ec[];

int func_02094294(void *a, void *b, void *c, void *d)
{
    Big big;
    int ret;
    int mode;
    unsigned char *tp;

    tp = (unsigned char *) data_021d52d8;
    func_02034270(&big, b, 0, 0);
    mode = big.unk_34;
    ret = 3;
    if (func_020ba4e4() == 1) {
        func_02091494(&data_021d5658, *(unsigned short *) (tp + 0x39c), a, b, c, d, -1);
        if (func_02090ac4(0x36, b, c, data_020e289c) != 0) {
            ret = 2;
        }
    } else if (func_020b6598() != 0 && mode == 3) {
        func_02091494(&data_021d5658, *(unsigned short *) (tp + 0x39c), a, b, c, 0, -1);
        if (func_02090ac4(0x35, b, c, data_020e28ec) != 0) {
            ret = 2;
        }
    } else {
        int k;
        if (mode == 0x13) {
            k = 0x34;
        } else {
            k = 0x33;
        }
        ret = func_02094cf8(k, a, b, c, d, 0);
    }
    func_0203423c(&big);
    return ret;
}
