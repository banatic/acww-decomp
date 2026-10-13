/* func_ov072_02278a54 @ 0x02278a54, 0x60 bytes, Thumb, module ov072
 * mwccarm 1.2/base -O4,s
 */

struct FuncTable {
    void *unk_00;
    void *unk_04;
    int (*unk_08)(void *self);
};

struct UnkStruct_02278a54 {
    struct FuncTable *funcs;
};

struct UnkStruct_02278a54_2 {
    char pad_00[0x658];
    struct UnkStruct_02278a54 sub658;
};

extern void *func_0201c2a4(struct UnkStruct_02278a54_2 *self, int n);
extern void func_02016108(struct UnkStruct_02278a54 *sub, void *val);
extern void func_ov072_02279628(struct UnkStruct_02278a54_2 *self, int code);
extern int func_02087178(void *addr);
extern int data_021ebcd2;

void func_ov072_02278a54(struct UnkStruct_02278a54_2 *self, int msg)
{
    void *v;

    switch (msg) {
        case 0:
            self->sub658.funcs->unk_08(&self->sub658);
            v = func_0201c2a4(self, 4);
            func_02016108(&self->sub658, v);
            func_ov072_02279628(self, 2);
            break;
        case 8:
            if (func_02087178(&data_021ebcd2) != 0) {
                func_ov072_02279628(self, 1);
            } else {
                func_ov072_02279628(self, 0);
            }
            break;
        default:
            break;
    }
}
