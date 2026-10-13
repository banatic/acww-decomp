/* func_ov096_0229dea4 @ 0x0229dea4, 0x58 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229de0c(void *self);
extern int func_ov096_0229ddfc(void *self);
extern int func_ov096_0229f810(void *self, int flag);
extern void func_ov096_0229dc28(void *self);
extern void func_ov002_0220a0b4(void *obj, int a, int b);
extern void func_ov002_0220a374(void *obj, int v);

typedef struct UnkStruct_0229dea4 {
    int pad_00;
} UnkStruct_0229dea4;

typedef struct UnkStruct_0229dea4_2 {
    unsigned char pad_00[0xb5];
    unsigned char unk_B5;
    unsigned char pad_B6[0x2500 - 0xb5 - 1];
    UnkStruct_0229dea4 obj;
} UnkStruct_0229dea4_2;

void func_ov096_0229dea4(UnkStruct_0229dea4_2 *self)
{
    int a;
    int b;

    a = func_ov096_0229de0c(self);
    b = func_ov096_0229ddfc(self);
    func_ov002_0220a0b4(&self->obj, a, b);

    if (func_ov096_0229f810(self, self->unk_B5) != 0) {
        func_ov002_0220a374(&self->obj, 0xd);
    } else {
        func_ov002_0220a374(&self->obj, 1);
    }

    func_ov096_0229dc28(self);
}
