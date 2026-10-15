/* func_ov096_0229d664 @ 0x0229d664, 0x78 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

struct St {
    char pad_00[0xA4];
    int unk_A4;
    int unk_A8;
    unsigned short unk_AC;
    char pad_AE[2];
    unsigned char unk_B0;
    char pad_B1[5];
    unsigned char unk_B6;
    char pad_B7[0x2A1];
    char unk_358[1];
};

extern void func_ov096_0229e9a0(struct St *self, unsigned char b);
extern int func_ov096_0229f290(struct St *self, unsigned char b);
extern int func_ov096_0229f200(struct St *self, unsigned char b);
extern int func_0206fe54(void);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov094_0229a47c(void *ptr, unsigned short a, unsigned char b);

void func_ov096_0229d664(struct St *self)
{
    unsigned char b;
    b = self->unk_B6;
    func_ov096_0229e9a0(self, b);
    self->unk_A4 = func_ov096_0229f290(self, b);
    self->unk_A8 = func_ov096_0229f200(self, b);
    if (func_0206fe54() != 0) {
        self->unk_A4 -= 2;
        self->unk_A8 -= 2;
    }
    func_ov002_02208098((void *) (self), 0x2B);
    func_ov094_0229a47c(&self->unk_358[0], self->unk_AC, self->unk_B0);
}
