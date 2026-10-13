/* func_ov111_022a021c @ 0x022a021c, 0x30 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
typedef struct {
    char pad_00[0x98];
    unsigned char unk_98;
} ParamType;
extern void func_ov002_02208098(ParamType *param, unsigned char byte);
extern void func_ov111_0229efec(ParamType *param);
void func_ov111_022a021c(ParamType *param)
{
    if ((data_021fbe40 & 0x100) == 0) {
        func_ov002_02208098(param, param->unk_98);
        func_ov111_0229efec(param);
    }
}
