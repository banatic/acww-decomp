/* func_ov003_02212a54 @ 0x02212a54, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int x;
    unsigned int y;
    unsigned int z;
    signed short angle;
    unsigned char flag;
} UnkStruct_02212a54;

typedef struct {
    unsigned int x;
    unsigned int y;
    unsigned int z;
} UnkStruct_02212a54_2;

typedef struct {
    unsigned char pad_00[0x98];
    unsigned int unk_98;
    unsigned char pad_9C[0x6f4 - 0x9c];
    unsigned int unk_6F4;
    unsigned char pad_6F8[4];
    unsigned int unk_6FC;
    unsigned char pad_700[0x7d4 - 0x700];
    UnkStruct_02212a54 obj;
} UnkStruct_02212a54_3;

extern void func_0200fa8c(UnkStruct_02212a54_2 *loc, UnkStruct_02212a54_3 *self);
extern int func_020e8ed8(int a, int b);
extern void func_0200fb34(UnkStruct_02212a54_3 *self, int angle);

void func_ov003_02212a54(UnkStruct_02212a54_3 *self)
{
    UnkStruct_02212a54 *obj = &self->obj;
    int angle;

    if (self->unk_98 == 0 && obj->flag == 0) {
        UnkStruct_02212a54_2 local;
        func_0200fa8c(&local, self);
        angle = func_020e8ed8(local.x - self->unk_6F4, local.z - self->unk_6FC);
        obj->angle = (signed short) angle;
        obj->flag = 1;
        obj->x = local.x;
        obj->y = local.y;
        obj->z = local.z;
    } else {
        angle = obj->angle;
    }
    func_0200fb34(self, angle);
}
