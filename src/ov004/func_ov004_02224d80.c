/* func_ov004_02224d80 @ 0x02224d80, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov004_02254918;
extern void *func_ov004_022254ac(void *ptr);
extern void *func_0202ee5c(void *ptr);

typedef struct {
    void *unk_00;
    char pad_04[0x654];
    char sub;
} UnkStruct_02224d80;

void *func_ov004_02224d80(UnkStruct_02224d80 *param)
{
    param->unk_00 = &data_ov004_02254918;
    func_ov004_022254ac(&param->sub);
    func_0202ee5c(param);
    return param;
}
