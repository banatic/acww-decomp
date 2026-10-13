/* func_ov110_0229ca48 @ 0x0229ca48, 0x34 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229cc14(void *self);
extern int func_ov110_0229cc04(void *self);
extern void func_ov002_0220a0b4(int *ptr, int a, int b);
extern void func_ov002_0220a374(int *ptr, int flag);

typedef struct {
    char pad_00[0x22e0];
    int unk_22E0;
} UnkStruct_0229ca48;

void func_ov110_0229ca48(UnkStruct_0229ca48 *self)
{
    int a, b;
    a = func_ov110_0229cc14(self);
    b = func_ov110_0229cc04(self);
    func_ov002_0220a0b4(&self->unk_22E0, a, b);
    func_ov002_0220a374(&self->unk_22E0, 1);
}
