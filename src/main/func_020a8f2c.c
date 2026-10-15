/* func_020a8f2c @ 0x020a8f2c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02050cb4(void *, int, int, int);
extern char data_020e3dac;

typedef struct {
    void *unk_00;
    char pad_04[0x78];
    int unk_7C;
    int unk_80;
} UnkStruct_020a8f2c;

UnkStruct_020a8f2c *func_020a8f2c(UnkStruct_020a8f2c *param, int argument1, int argument2, int argument3)
{
    func_02050cb4(param, (int) argument1, (int) argument2, (int) argument3);
    param->unk_00 = &data_020e3dac;
    param->unk_7C = 0;
    param->unk_80 = 0;
    return param;
}
