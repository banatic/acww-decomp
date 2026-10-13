/* func_ov110_0229cc58 @ 0x0229cc58, 0x58 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229cc14(void *self);
extern int func_ov110_0229cc04(void *self);
extern int func_ov110_0229d5c8(void *self, int flag);
extern void func_ov110_0229ca28(void *self);
extern void func_ov002_0220a0b4(void *obj, int a, int b);
extern void func_ov002_0220a374(void *obj, int v);

typedef struct UnkStruct_0229cc58 {
    int pad_00;
} UnkStruct_0229cc58;

typedef struct UnkStruct_0229cc58_2 {
    unsigned char pad_00[0xf5];
    unsigned char unk_F5;
    unsigned char pad_F6[0x22e0 - 0xf5 - 1];
    UnkStruct_0229cc58 obj;
} UnkStruct_0229cc58_2;

void func_ov110_0229cc58(UnkStruct_0229cc58_2 *self)
{
    int a;
    int b;

    a = func_ov110_0229cc14(self);
    b = func_ov110_0229cc04(self);
    func_ov002_0220a0b4(&self->obj, a, b);

    if (func_ov110_0229d5c8(self, self->unk_F5) != 0) {
        func_ov002_0220a374(&self->obj, 7);
    } else {
        func_ov002_0220a374(&self->obj, 1);
    }

    func_ov110_0229ca28(self);
}
