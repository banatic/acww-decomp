/* func_ov003_0221292c @ 0x0221292c, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct FuncOv003Struct {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
};

extern int func_02008258(void *, int);
extern int func_02056f94(void *);
extern void func_020109fc(void *, int, int, int);

void func_ov003_0221292c(struct FuncOv003Struct *self)
{
    self->unk_7FC = func_02008258(self, self->unk_7F0);
    if (func_02056f94((char *) self + 0x2d0) != 0) {
        func_020109fc(self, 0x4a, 3, 0);
    }
}
