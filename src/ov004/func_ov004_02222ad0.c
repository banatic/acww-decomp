/* func_ov004_02222ad0 @ 0x02222ad0, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov004_0225445c;
extern void *func_ov004_02222efc(void *ptr);
extern void *func_0202ee5c(void *ptr);

typedef struct {
    void *unk_00;
    char pad_04[0x654];
    char sub;
} UnkStruct_02222ad0;

void *func_ov004_02222ad0(UnkStruct_02222ad0 *param)
{
    param->unk_00 = &data_ov004_0225445c;
    func_ov004_02222efc(&param->sub);
    func_0202ee5c(param);
    return param;
}
