/* func_ov004_02223654 @ 0x02223654, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov004_022546e0;
extern void func_ov004_02224580(void *ptr);
extern void func_0202ee5c(void *ptr);

typedef struct {
    void *unk_00;
    char pad_04[0x654];
    char sub;
} UnkStruct_02223654;

void *func_ov004_02223654(UnkStruct_02223654 *param)
{
    param->unk_00 = &data_ov004_022546e0;
    func_ov004_02224580(&param->sub);
    func_0202ee5c(param);
    return param;
}
