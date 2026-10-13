/* func_ov100_0229c60c @ 0x0229c60c, 0xd0 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x2274];
    char unk_2274;
    unsigned char pad_2275[0x6ac];
    unsigned char byte_field;
} UnkStruct_0229c60c;

extern void func_ov100_0229c2a0(UnkStruct_0229c60c *self, int x);
extern void func_ov100_0229c2b0(UnkStruct_0229c60c *self, int x);
extern void func_ov100_0229c84c(UnkStruct_0229c60c *self, int a, int b);
extern void func_ov100_0229c758(UnkStruct_0229c60c *self, int a, int b);
extern void func_ov100_0229c6dc(UnkStruct_0229c60c *self, int a);
extern int func_ov100_0229d630(UnkStruct_0229c60c *self, unsigned char byte);
extern int func_ov100_0229d620(UnkStruct_0229c60c *self, unsigned char byte);
extern int func_ov100_0229d60c(UnkStruct_0229c60c *self, unsigned char byte);
extern void func_ov002_0220a314(void *ptr);
extern void func_ov002_0220a2b4(void *ptr);

int func_ov100_0229c60c(UnkStruct_0229c60c *self, int a, int b)
{
    unsigned char initial = self->byte_field;
    func_ov100_0229c2a0(self, 0x30);
    func_ov100_0229c2a0(self, 0x100);
    if (a == 0) {
        return 0;
    }
    if (func_ov100_0229d630(self, self->byte_field)) {
        func_ov100_0229c84c(self, a, b);
    } else if (func_ov100_0229d620(self, self->byte_field)) {
        func_ov100_0229c758(self, a, b);
    } else if (func_ov100_0229d60c(self, self->byte_field)) {
        func_ov100_0229c6dc(self, a);
    }
    {
        int result1 = func_ov100_0229d60c(self, self->byte_field);
        int result2 = func_ov100_0229d60c(self, initial);
        if (result1 != result2) {
            if (func_ov100_0229d60c(self, self->byte_field) != 0) {
                func_ov002_0220a314(&self->unk_2274);
            } else {
                func_ov002_0220a2b4(&self->unk_2274);
            }
            func_ov100_0229c2b0(self, 0x100);
        }
    }
    return (initial != self->byte_field) ? 1 : 0;
}
