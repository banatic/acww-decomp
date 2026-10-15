/* func_ov099_0229d050 @ 0x0229d050, 0xa0 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229d050 {
    unsigned char pad_00[0x27f0];
    int unk_27F0;
    int unk_27F4;
    unsigned char pad_27F8[0x2904 - 0x27f8];
    unsigned char unk_2904;
    unsigned char unk_2905;
};

unsigned char *func_ov002_02208098(struct UnkStruct_0229d050 *self, unsigned char value);
int func_ov099_0229cd70(struct UnkStruct_0229d050 *self, int param);
int func_ov099_0229cd1c(struct UnkStruct_0229d050 *self, int param);
void func_ov002_02207cf8(void *ptr);
int func_ov099_0229cf20(struct UnkStruct_0229d050 *self, int param);
int func_ov099_0229ccc8(struct UnkStruct_0229d050 *self, int param);
void func_ov099_0229c28c(struct UnkStruct_0229d050 *self, int param);
void func_ov099_0229c29c(struct UnkStruct_0229d050 *self, int param);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

void func_ov099_0229d050(struct UnkStruct_0229d050 *self, unsigned char param)
{
    unsigned char g1;
    unsigned char g2;

    self->unk_2904 = param;
    func_ov002_02208098(self, 1);
    g1 = data_021f6c58;
    g2 = data_021f6c54;
    self->unk_27F0 = func_ov099_0229cd70(self, self->unk_2904) - g1;
    self->unk_27F4 = func_ov099_0229cd1c(self, self->unk_2904) - g2;
    self->unk_2905 = param;
    func_ov002_02207cf8((char *) self + 0x218c);
    if (func_ov099_0229cf20(self, param) != 0) {
        func_ov099_0229c28c(self, 4);
    } else if (func_ov099_0229ccc8(self, param) != 0) {
        func_ov099_0229c28c(self, 4);
    } else {
        func_ov099_0229c29c(self, 4);
    }
}
