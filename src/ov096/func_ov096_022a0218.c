/* func_ov096_022a0218 @ 0x022a0218, 0x5c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xae];
    unsigned short unk_AE;
    unsigned char pad_B0[4];
    unsigned char unk_B4;
    unsigned char pad_B5[4];
    unsigned char unk_B9;
} FuncOv096Struct;

extern void func_ov096_0229e898(void *self, unsigned char a, int b);
extern int func_ov096_0229c2fc(void *self, int value);
extern unsigned char *func_ov096_0229f8cc(void *self, unsigned char b4, unsigned char b9, unsigned short ae, int zero);
extern void func_ov096_0229c2dc(void *self, int value);
extern void func_ov094_022999d8(void);
extern void func_ov096_0229fb9c(void *self);

void func_ov096_022a0218(FuncOv096Struct *self)
{
    func_ov096_0229e898(self, self->unk_B4, 1);
    if (func_ov096_0229c2fc(self, 0x2000) != 0) {
        func_ov096_0229f8cc(self, self->unk_B4, self->unk_B9, self->unk_AE, 0);
        func_ov096_0229c2dc(self, 0x2000);
    } else {
        func_ov094_022999d8();
        func_ov096_0229fb9c(self);
    }
}
