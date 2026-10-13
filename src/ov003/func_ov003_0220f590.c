/* func_ov003_0220f590 @ 0x0220f590, 0x68 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0220f590;
typedef struct {
    int a;
    int b;
} UnkStruct_0220f590_2;
extern int func_02073908(int *a, int b);
extern void func_02010d64(struct UnkStruct_0220f590 *self);
extern int func_0200f530(struct UnkStruct_0220f590 *self, UnkStruct_0220f590_2 *local);
extern void func_ov003_0220f684(struct UnkStruct_0220f590 *self);
extern void func_ov003_0220f658(struct UnkStruct_0220f590 *self);
extern void func_ov003_0220f5f8(struct UnkStruct_0220f590 *self);
extern int *data_020ccf94;
typedef struct {
    int pad_00;
    int a;
    int b;
} UnkStruct_0220f590_3;
struct UnkStruct_0220f590 {
    unsigned char pad_00[0x7d4];
    UnkStruct_0220f590_3 sub;
    unsigned char pad_7E0[0x20];
    int unk_800;
};

void func_ov003_0220f590(struct UnkStruct_0220f590 *self)
{
    UnkStruct_0220f590_3 *sub = &self->sub;
    int b;
    UnkStruct_0220f590_2 local;

    func_ov003_0220f684(self);
    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        func_ov003_0220f658(self);
        func_02010d64(self);
    } else {
        b = sub->b;
        local.a = sub->a;
        local.b = b;
        if (func_0200f530(self, &local) != 0) {
            func_ov003_0220f658(self);
        }
        func_02010d64(self);
    }
    func_ov003_0220f5f8(self);
}
