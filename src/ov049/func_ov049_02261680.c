/* func_ov049_02261680 @ 0x02261680, 0x9c bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern char *data_ov049_02263298;
extern int func_0201b3c0(void *a, void *b, void *c);
extern void func_0201b3a4(void *a, void *b);
extern void func_0206844c(void *a, char *b, char *c);
extern void func_0206fa8c(int a);

typedef struct UnkStruct_02261680 UnkStruct_02261680;
struct UnkStruct_02261680 {
    unsigned char pad_00[0x40];
    void *unk_40;
    unsigned char pad_44[0xb0 - 0x44];
    void *unk_B0;
    unsigned char pad_B4[0xbc - 0xb4];
    void *unk_BC;
    void *unk_C0;
};

void func_ov049_02261680(UnkStruct_02261680 *self, int mode)
{
    char buf[3];

    switch (mode) {
        case 0: {
            int ret = func_0201b3c0(self->unk_B0, self->unk_BC, self->unk_C0);
            switch (ret) {
                case 0:
                    func_0201b3a4(self->unk_B0, self->unk_BC);
                    buf[0] = 0x1a;
                    func_0206844c(self->unk_40, &buf[0], data_ov049_02263298);
                    break;
                case 1:
                    buf[1] = 0x1e;
                    func_0206844c(self->unk_40, &buf[1], data_ov049_02263298);
                    break;
                case 2:
                    buf[2] = 0x38;
                    func_0206844c(self->unk_40, &buf[2], data_ov049_02263298);
                    func_0206fa8c(0);
                    break;
                default:
                    break;
            }
            break;
        }
        case 1:
            func_0206fa8c(0);
            break;
        default:
            break;
    }
}
