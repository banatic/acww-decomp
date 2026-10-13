/* func_ov107_0229cba4 @ 0x0229cba4, 0x70 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208c58(char *a, char *b, int c);
extern int func_ov107_0229d29c(void *self, unsigned char b);
extern int func_ov107_0229d260(void *self, unsigned char b);
extern void func_ov002_02209874(char *a, char *b);
extern void func_ov002_02209910(char *a, int b, int c);
extern void func_ov002_0220970c(char *a, int b);
extern void func_ov002_02208098(void *self, int k);

typedef struct {
    char pad_00[0xb9];
    unsigned char unk_B9;
    char pad_BA[0x2112];
    char unk_21CC[1];
    char pad_21CD[0x14b];
    char unk_2318[0x3e8];
    char unk_2700[1];
} UnkStruct_0229cba4;

void func_ov107_0229cba4(UnkStruct_0229cba4 *self, int flag)
{
    int ret1, ret2;

    func_ov002_02208c58(self->unk_2318, self->unk_2700, 0);
    ret1 = func_ov107_0229d29c(self, self->unk_B9);
    ret2 = func_ov107_0229d260(self, self->unk_B9);

    if (flag != 0) {
        func_ov002_02209874(self->unk_2318, self->unk_21CC);
    } else {
        func_ov002_02209910(self->unk_2318, ret1, ret2);
    }

    func_ov002_0220970c(self->unk_2318, 0);
    func_ov002_02208098(self, 0xb);
}
