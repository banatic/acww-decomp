/* func_ov105_0229cf10 @ 0x0229cf10, 0x38 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a05c(void *dst, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *obj, unsigned char value);

typedef struct {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[0x22f];
    unsigned char unk_2BD;
    unsigned char pad_2BE[0x24a4 - 0x2bd - 1];
    unsigned char data[1];
} UnkStruct_0229cf10;

void func_ov105_0229cf10(UnkStruct_0229cf10 *self, int a, int b)
{
    func_ov002_0220a05c(&self->data[0], a, b, 3, 1);
    self->unk_2BD = self->unk_8D;
    func_ov002_02208098(self, 0xd);
}
