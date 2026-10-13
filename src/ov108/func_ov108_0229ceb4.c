/* func_ov108_0229ceb4 @ 0x0229ceb4, 0x98 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x9c];
    int unk_9C;
    int unk_A0;
    char pad_A4[0x2ad - 0xa4];
    unsigned char unk_2AD;
    unsigned char unk_2AE;
    char pad_2AF[0x2b6 - 0x2af];
    unsigned char unk_2B6;
    char pad_2B7[0x23b0 - 0x2b7];
    char unk_23B0;
} UnkStruct_0229ceb4;

extern void func_ov002_02208098(void *, int);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov108_0229cc20(void *, unsigned char);
extern int func_ov108_0229cbe4(void *, unsigned char);
extern void func_ov002_02207cf8(void *);
extern void func_ov002_02207d00(void *);
extern int func_ov108_0229cb88(void *, int);
extern void func_ov108_0229c2bc(void *, int);
extern void func_ov108_0229c2cc(void *, int);

void func_ov108_0229ceb4(UnkStruct_0229ceb4 *self, int arg1)
{
    unsigned char v1, v2;
    int res;

    self->unk_2AD = (unsigned char) arg1;
    func_ov002_02208098(self, 1);
    v1 = data_021f6c58;
    v2 = data_021f6c54;
    res = func_ov108_0229cc20(self, self->unk_2AD);
    self->unk_9C = res - v1;
    res = func_ov108_0229cbe4(self, self->unk_2AD);
    self->unk_A0 = res - v2;
    self->unk_2AE = (unsigned char) arg1;
    func_ov002_02207cf8(&self->unk_23B0);
    func_ov002_02207d00(&self->unk_23B0);
    self->unk_2B6 = 2;
    if (func_ov108_0229cb88(self, arg1) != 0) {
        func_ov108_0229c2bc(self, 4);
    } else {
        func_ov108_0229c2cc(self, 4);
    }
}
