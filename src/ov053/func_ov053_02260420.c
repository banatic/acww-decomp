/* func_ov053_02260420 @ 0x02260420, 0x28 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov053_02261b98;

typedef struct Sub658 {
    int pad_00;
} Sub658;

typedef struct UnkStruct_02260420 {
    void *unk_00;
    char pad_04[0x654];
    Sub658 sub658;
} UnkStruct_02260420;

extern void func_ov053_02260bfc(Sub658 *);
extern void func_0202ee5c(UnkStruct_02260420 *);

UnkStruct_02260420 *func_ov053_02260420(UnkStruct_02260420 *obj)
{
    obj->unk_00 = &data_ov053_02261b98;
    func_ov053_02260bfc(&obj->sub658);
    func_0202ee5c(obj);
    return obj;
}
