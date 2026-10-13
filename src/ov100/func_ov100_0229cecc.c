/* func_ov100_0229cecc @ 0x0229cecc, 0x64 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229d630(void *self, unsigned char byte);
extern int func_ov100_0229d620(void *self, unsigned char byte);
extern int func_ov100_0229d158(void *self, unsigned char byte);
extern void func_ov002_02207cf0(void *ptr);
extern void func_ov002_02207cf8(void *ptr);

typedef struct {
    char pad_00[0x218c];
    unsigned char unk_218C;
    char pad_218D[0x792];
    unsigned char unk_291F;
    char pad_2920[0x1];
    unsigned char unk_2921;
} Object;

void func_ov100_0229cecc(Object *self)
{
    if (func_ov100_0229d630(self, self->unk_2921) != 0 || func_ov100_0229d620(self, self->unk_2921) != 0) {
        if (func_ov100_0229d158(self, self->unk_2921) != 0) {
            func_ov002_02207cf0((void *) &self->unk_218C);
        } else {
            self->unk_291F = self->unk_2921;
            func_ov002_02207cf8((void *) &self->unk_218C);
        }
    } else {
        func_ov002_02207cf0((void *) &self->unk_218C);
    }
}
