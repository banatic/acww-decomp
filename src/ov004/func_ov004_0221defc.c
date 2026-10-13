/* func_ov004_0221defc @ 0x0221defc, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202dc3c(void *ptr, int value, int count);

typedef struct {
    char pad_00[0x1a4];
    int unk_1A4;
} UnkStruct_0221defc;

void func_ov004_0221defc(UnkStruct_0221defc *obj, int val)
{
    func_0202dc3c(obj, val, 0x11);
    obj->unk_1A4 = val;
}
