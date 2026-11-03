/* turtle_fishing: 2 functions, module ov081
 * mwccarm 1.2/base -O4,s
 * func_ov081_02278a28 @ 0x02278a28, 0x2c bytes, Thumb
 * func_ov081_02278a00 @ 0x02278a00, 0x28 bytes, Thumb
 */

struct UnkStruct_02278a28 {
    char pad_00;
};

struct UnkStruct_02278a28_2 {
    char *unk_00;
    char pad_04[0x658 - 4];
    struct UnkStruct_02278a28 sub;
};

typedef struct {
    char *unk_00;
    char pad_04[0x654];
} UnkStruct_02278a00;

extern void *func_ov081_02279024(struct UnkStruct_02278a28 *);
extern void *func_0202ee5c(struct UnkStruct_02278a28_2 *);
extern void func_020edf54(struct UnkStruct_02278a28_2 *);
extern char data_ov081_022797bc[];

struct UnkStruct_02278a28_2 *func_ov081_02278a28(struct UnkStruct_02278a28_2 *obj)
{
    obj->unk_00 = ((char *) data_ov081_022797bc);
    func_ov081_02279024(&obj->sub);
    func_0202ee5c(obj);
    func_020edf54(obj);
    return obj;
}

UnkStruct_02278a00 *func_ov081_02278a00(UnkStruct_02278a00 *self)
{
    self->unk_00 = data_ov081_022797bc;
    func_ov081_02279024((struct UnkStruct_02278a28 *) ((char *) self + 0x658));
    func_0202ee5c((struct UnkStruct_02278a28_2 *) self);
    return self;
}
