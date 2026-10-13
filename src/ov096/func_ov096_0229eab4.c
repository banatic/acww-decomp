/* func_ov096_0229eab4 @ 0x0229eab4, 0x60 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229eab4 {
    char pad_00[0xa4];
    int unk_A4;
    int unk_A8;
    char pad_AC[0xb1 - 0xac];
    unsigned char unk_B1;
};

extern int func_ov096_0229c2fc(void *self, int flag);
extern void func_ov094_0229a6bc(void *addr, int a4, int a8);
extern void func_ov094_0229b5e8(void *addr, int a4, int a8, void *addr2);

void func_ov096_0229eab4(struct UnkStruct_0229eab4 *self)
{
    unsigned char mode;

    if (func_ov096_0229c2fc(self, 0x40) != 0) {
        return;
    }
    mode = self->unk_B1;
    if (mode == 0) {
        return;
    }
    if (mode == 2) {
        func_ov094_0229a6bc((char *) self + 0x358, self->unk_A4, self->unk_A8);
        return;
    }
    if (mode == 1) {
        func_ov094_0229b5e8((char *) self + 0xdb8, self->unk_A4, self->unk_A8, (char *) self + 0x2e28);
    }
}
