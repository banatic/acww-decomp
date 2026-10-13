/* func_0203af80 @ 0x0203af80, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0203af80 {
    int a;
    int b;
    int c;
};

struct GStruct {
    char pad_00[0x1ca];
    unsigned char unk_1CA;
    char pad_1CB[1];
    int unk_1CC[3];
    char pad_1D8[0x1f8 - 0x1cc - 12];
    int unk_1F8;
};

extern struct GStruct *data_021c67a4;
extern int func_020b65c4(void);
extern int func_02095794(int);
extern int func_0203b0b8(int, struct UnkStruct_0203af80 *, int, int);
extern int func_0203b144(void);
extern int func_0203c0ac(struct GStruct *, int);

int func_0203af80(struct UnkStruct_0203af80 *param)
{
    if (data_021c67a4->unk_1F8 == 9) {
        return 0;
    }
    if (func_020b65c4() == 0xc) {
        return 0;
    }
    if (func_0203b0b8(func_02095794(4), param, 0, 0) >= 0xb000) {
        return func_0203b144();
    } else {
        int *p;
        data_021c67a4->unk_1CA = 0;
        p = data_021c67a4->unk_1CC;
        p[0] = param->a;
        p[1] = param->b;
        p[2] = param->c;
        return func_0203c0ac(data_021c67a4, 2);
    }
}
