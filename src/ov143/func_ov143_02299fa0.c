/* func_ov143_02299fa0 @ 0x02299fa0, 0x30 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a05c(void *p, int a, int b, int c, int d);
extern void func_ov002_02208098(void *p, int n);

typedef struct {
    char pad_00[0x8d];
    unsigned char unk_8D;
    char pad_8E[0x10];
    unsigned char unk_9E;
    char pad_9F[0xd];
    char unk_AC;
} UnkStruct_02299fa0;

void func_ov143_02299fa0(UnkStruct_02299fa0 *self, int a, int b)
{
    func_ov002_0220a05c(&self->unk_AC, a, b, 3, 1);
    self->unk_9E = self->unk_8D;
    func_ov002_02208098(self, 4);
}
