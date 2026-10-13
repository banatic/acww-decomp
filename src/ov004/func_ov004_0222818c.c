/* func_ov004_0222818c @ 0x0222818c, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(int *p);
extern void func_020109fc(void *self, int a, int b, int c);
extern int func_02073908(int a, int b);
extern int func_02008258(void *self, int a);
extern int data_020ccf94;

typedef struct UnkStruct_0222818c {
    char pad_00[0x2d0];
    int unk_2D0;
    char pad_2D4[0x7f0 - 0x2d0 - 4];
    int unk_7F0;
    char pad_7F4[0x7fc - 0x7f0 - 4];
    int unk_7FC;
    int unk_800;
} UnkStruct_0222818c;

void func_ov004_0222818c(UnkStruct_0222818c *self)
{
    if (func_02056f94(&self->unk_2D0) == 0) {
        return;
    }
    func_020109fc(self, 0x0, 3, 3);
    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        return;
    }
    self->unk_7FC = func_02008258(self, self->unk_7F0);
}
