/* func_ov081_02278a00 @ 0x02278a00, 0x28 bytes, Thumb, module ov081
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov081_02279024(void *ptr);
extern void func_0202ee5c(void *ptr);
extern char data_ov081_022797bc[];

typedef struct {
    char *unk_00;
    char pad_04[0x654];
} UnkStruct_02278a00;

UnkStruct_02278a00 *func_ov081_02278a00(UnkStruct_02278a00 *self)
{
    self->unk_00 = data_ov081_022797bc;
    func_ov081_02279024((char *) self + 0x658);
    func_0202ee5c(self);
    return self;
}
