/* func_ov112_022a0a0c @ 0x022a0a0c, 0x30 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern void func_ov002_02208098(void *param, unsigned char b);
extern void func_ov112_0229f488(void *param);

typedef struct {
    char pad_00[0xc1];
    unsigned char unk_C1;
} Param_t;

void func_ov112_022a0a0c(Param_t *param)
{
    if ((data_021fbe40 & 0x200) == 0) {
        func_ov002_02208098(param, param->unk_C1);
        func_ov112_0229f488(param);
    }
}
