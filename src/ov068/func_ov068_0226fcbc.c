/* func_ov068_0226fcbc @ 0x0226fcbc, 0x6c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0226fcbc UnkStruct_0226fcbc;
struct UnkStruct_0226fcbc {
    char pad_00[0x5c];
    char unk_5C[0x210];
    int unk_26C;
    char pad_270[0x98];
    char unk_308[0x20];
    char unk_328[0x10];
};

extern void func_01ffd070(void *, void *, void *);
extern short FX_Div(int, int);
extern void func_020912d4(int, void *, int, void *);
extern void func_020044c0(void *, unsigned, unsigned, int);

void func_ov068_0226fcbc(UnkStruct_0226fcbc *param)
{
    short result;
    int buffer[2];

    func_01ffd070(buffer, param->unk_5C, param->unk_308);
    buffer[1] += param->unk_26C - 0x400;
    result = FX_Div(param->unk_26C, 0x1000);
    func_020912d4(0x3e, buffer, 0, &result);
    func_020044c0(param->unk_328, 0x81f, 0x7f, 0);
}
