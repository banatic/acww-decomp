/* func_ov003_0220f294 @ 0x0220f294, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void *ptr);
extern int func_02056f94(void *ptr);
extern void func_020109fc(void *ptr, int a, int b, int c);
extern int func_02073908(unsigned int a, int b);
extern int func_02008258(void *ptr, int b);
extern unsigned int data_020ccf94;

typedef struct {
    char pad_00[0x2d0];
    char unk_2D0;
    char pad_2D1[0x7f0 - 0x2d0 - 1];
    int unk_7F0;
    char pad_7F4[0x7fc - 0x7f0 - 4];
    int unk_7FC;
    int unk_800;
} SelfType;

void func_ov003_0220f294(SelfType *self)
{
    func_02010f5c(self);
    if (func_02056f94(&self->unk_2D0) != 0) {
        func_020109fc(self, 0, 3, 3);
        if (func_02073908(data_020ccf94, self->unk_800) == 0) {
            self->unk_7FC = func_02008258(self, self->unk_7F0);
        }
    }
}
