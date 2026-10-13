/* func_020a8f2c @ 0x020a8f2c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02050cb4(void *);
extern char data_020e3dac;

typedef struct {
    void *unk_00;
    char pad_04[0x78];
    int unk_7C;
    int unk_80;
} UnkStruct_020a8f2c;

UnkStruct_020a8f2c *func_020a8f2c(UnkStruct_020a8f2c *param)
{
    func_02050cb4(param);
    param->unk_00 = &data_020e3dac;
    param->unk_7C = 0;
    param->unk_80 = 0;
    return param;
}
