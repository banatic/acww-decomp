/* func_ov103_0229ca9c @ 0x0229ca9c, 0x6c bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x0b2c];
    char unk_B2C;
    char pad_B2D[0x218c - 0x0b2c - 1];
    char unk_218C;
    char pad_218D[0x2da2 - 0x218c - 1];
    unsigned char unk_2DA2;
} param_t;

extern int func_ov103_0229ccb4(param_t *param, unsigned char byte);
extern int func_ov103_0229cc80(param_t *param, unsigned char byte);
extern int func_0206fe54(void);
extern void func_0208aa60(void *ptr, int a, int b);
extern int func_ov103_0229cdfc(param_t *param, unsigned char byte);
extern int func_ov103_0229cde8(param_t *param, unsigned char byte);
extern int func_ov094_0229b9b4(void *a, void *b, int c);

void func_ov103_0229ca9c(param_t *param)
{
    int r6 = func_ov103_0229ccb4(param, param->unk_2DA2) - 0x6d;
    int r4 = func_ov103_0229cc80(param, param->unk_2DA2) - 0x78;
    if (func_0206fe54()) {
        r4 -= 8;
    }
    func_0208aa60(&param->unk_218C, r6, r4);
    if (func_ov103_0229cdfc(param, param->unk_2DA2) != 0) {
        int ret = func_ov103_0229cde8(param, param->unk_2DA2);
        func_ov094_0229b9b4(&param->unk_B2C, &param->unk_218C, ret);
    }
}
