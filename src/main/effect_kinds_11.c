/* effect_kinds_11: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020946c4 @ 0x020946c4, 0x28 bytes, Thumb
 * func_0209469c @ 0x0209469c, 0x28 bytes, Thumb
 * func_0209458c @ 0x0209458c, 0x110 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x39c];
    unsigned short unk_39C;
} Cfg;

typedef struct {
    unsigned char pad_00[0x34];
    int mode;
    unsigned char pad_38[0x8];
} UnkStruct_0209458c;

extern int func_020948b8(int p1, int p2, void *p3, int p4, void *p5, int p6, void *p7, int p8, int p9);
extern unsigned char data_020e29dc[];
extern int func_02034270(void *obj, int a, int b, int c);
extern void func_0203423c(void *obj);
extern int func_02094cf8(int kind, int a0, int a1, int a2, int a3, void *tbl);
extern void func_02091494(void *ctx, int hw, int a0, int a1, int a2, int a3, int minus1);
extern int func_02090ac4(int kind, int a1, int a2, void *tbl);
extern int func_020ba4e4(void);
extern int func_020b6598(void);
extern unsigned char data_020e54a8;
extern int data_021d5658;
extern int data_020e27bc;
extern int data_020e27dc;
extern int data_020e27f4;
extern Cfg data_021d52d8;

int func_020946c4(int a)
{
    return func_020948b8(a, 31, (void *) data_020e29dc, 29, (void *) data_020e29dc, 29, (void *) data_020e29dc, -1, 0);
}

void func_0209469c(int a)
{
    func_020948b8(a, 0x1f, ((char *) data_020e29dc), 0x1e, ((char *) data_020e29dc), 0x1e, ((char *) data_020e29dc), -1, 0);
}

int func_0209458c(int a, int b, int c, int d)
{
    UnkStruct_0209458c s;
    Cfg *cfg;
    int mode;
    int result;
    unsigned int cond;

    func_02034270(&s, b, 0, 0);
    mode = s.mode;
    result = 3;
    cfg = &data_021d52d8;
    cond = (data_020e54a8 == 1) ? 1 : 0;

    if (cond > 0) {
        if (mode == 9 || mode == 3) {
            result = func_02094cf8(0x19, a, b, c, d, &data_020e27bc);
        }
    } else {
        if (mode == 0x16 || func_020ba4e4() == 1) {
            func_02091494(&data_021d5658, cfg->unk_39C, a, b, c, 0, -1);
            if (func_02090ac4(0x1b, b, c, &data_020e27dc) != 0) {
                result = 2;
            }
        } else if (mode == 3 && func_020b6598() != 0) {
            func_02091494(&data_021d5658, cfg->unk_39C, a, b, c, 0, -1);
            if (func_02090ac4(0x1c, b, c, &data_020e27f4) != 0) {
                result = 2;
            }
        } else {
            result = func_02094cf8((mode == 0x13) ? 0x1a : 0x19, a, b, c, d, &data_020e27bc);
        }
    }

    func_0203423c(&s);
    return result;
}
