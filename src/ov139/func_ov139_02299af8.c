/* func_ov139_02299af8 @ 0x02299af8, 0x38 bytes, Thumb, module ov139
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220b04c(void *self, int offset, int value);
extern void func_ov002_0220b06c(void *self, int arg2, unsigned int a, unsigned int b);
extern void func_0208aa70(void *self);

typedef struct {
    char pad_00[0x9a0];
    unsigned short unk_9A0;
    unsigned char unk_9A2;
} UnkStruct_02299af8;

void func_ov139_02299af8(UnkStruct_02299af8 *self, unsigned char value, int arg2)
{
    self->unk_9A2 = value;
    self->unk_9A0 = 0;
    func_ov002_0220b04c(self, 0x9a0, 0);
    func_ov002_0220b06c(self, arg2, 0x90, 0x18);
    func_0208aa70(self);
}
