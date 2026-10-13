/* func_ov129_0229c418 @ 0x0229c418, 0x50 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov129_0229b7ec(void *self, int param);
extern int func_ov002_0220a72c(void *addr, int param);
extern const unsigned char data_ov129_0229db48[];

typedef struct {
    char pad_00[0x98];
    int unk_98;
    unsigned char pad_9C[0xae - 0x98 - 4];
    unsigned char unk_AE;
    char pad_AF[0x1d4 - 0xae - 1];
    char unk_1D4;
} UnkStruct_0229c418;

int func_ov129_0229c418(UnkStruct_0229c418 *self)
{
    if (func_ov129_0229b7ec(self, 2) != 0) {
        return self->unk_98;
    } else {
        unsigned char b = self->unk_AE;
        switch (b) {
            case 4:
                return func_ov002_0220a72c(&self->unk_1D4, 6);
            case 5:
                return func_ov002_0220a72c(&self->unk_1D4, 5);
            default:
                return data_ov129_0229db48[b];
        }
    }
}
