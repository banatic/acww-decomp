/* func_ov101_0229c548 @ 0x0229c548, 0x70 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208c58(char *a, char *b, int c);
extern int func_ov101_0229cd08(void *self, unsigned char b);
extern int func_ov101_0229ccd0(void *self, unsigned char b);
extern void func_ov002_02209874(char *a, char *b);
extern void func_ov002_02209910(char *a, int b, int c);
extern void func_ov002_0220970c(char *a, int b);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);

typedef struct {
    char pad_00[0xb4];
    unsigned char unk_B4;
    char pad_B5[0x20ff];
    char unk_21B4[1];
    char pad_21B5[0x14b];
    char unk_2300[0x3e8];
    char unk_26E8[1];
} UnkStruct_0229c548;

void func_ov101_0229c548(UnkStruct_0229c548 *self, int flag)
{
    int ret1, ret2;

    func_ov002_02208c58(self->unk_2300, self->unk_26E8, 0);
    ret1 = func_ov101_0229cd08(self, self->unk_B4);
    ret2 = func_ov101_0229ccd0(self, self->unk_B4);

    if (flag != 0) {
        func_ov002_02209874(self->unk_2300, self->unk_21B4);
    } else {
        func_ov002_02209910(self->unk_2300, ret1, ret2);
    }

    func_ov002_0220970c(self->unk_2300, 0);
    func_ov002_02208098(self, 0x13);
}
