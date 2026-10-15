/* func_ov116_0229de2c @ 0x0229de2c, 0x34 bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229de2c {
    char pad_00[0x8d];
    unsigned char unk_8D;
    char pad_8E[0x06];
    char unk_94;
    char pad_95[0x1397];
    unsigned char unk_142C;
};

extern void func_ov002_0220a05c(char *p, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(struct UnkStruct_0229de2c *p, unsigned char value);

void func_ov116_0229de2c(struct UnkStruct_0229de2c *self, int a, int b)
{
    func_ov002_0220a05c(&self->unk_94, a, b, 3, 1);
    self->unk_142C = self->unk_8D;
    func_ov002_02208098(self, 3);
}
