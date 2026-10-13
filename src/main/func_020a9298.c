/* func_020a9298 @ 0x020a9298, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020a9298 {
    void *unk_00;
} UnkStruct_020a9298;

extern char data_020e3de4;
extern void func_020a941c(UnkStruct_020a9298 *param);

UnkStruct_020a9298 *func_020a9298(UnkStruct_020a9298 *param)
{
    param->unk_00 = &data_020e3de4;
    func_020a941c(param);
    return param;
}
