/* func_ov094_0229a3b0 @ 0x0229a3b0, 0xb4 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_ov094_0229a39c(void);
extern void func_ov094_0229a464(void);
extern int func_ov094_0229b048(void *p, unsigned char a, unsigned char b);
extern void func_ov094_0229a8cc(void *self, const unsigned char *tab, int n, unsigned int m);
extern void func_ov094_0229a99c(void *self, unsigned short v, int n);

extern const unsigned char data_ov094_0229bc50[];
extern const unsigned char data_ov094_0229bf70[];

typedef struct UnkStruct_0229a3b0 UnkStruct_0229a3b0;
struct UnkStruct_0229a3b0 {
    unsigned char pad_00[0x184];
    unsigned char buf[0xa54 - 0x184];
    unsigned short unk_A54;
    unsigned char pad_A56[0xa59 - 0xa56];
    unsigned char unk_A59;
    unsigned char unk_A5A;
    unsigned char unk_A5B;
};

int func_ov094_0229a3b0(UnkStruct_0229a3b0 *self)
{
    unsigned char state = self->unk_A5A;

    if (state < 6) {
        if (data_ov094_0229bc50[state] != 0xff) {
            int r = func_ov094_0229b048(self->buf, data_ov094_0229bc50[state], self->unk_A5B);
            func_ov094_0229a8cc(self, data_ov094_0229bf70, r, 8);
        }
        self->unk_A5A++;
    } else if (state < 8) {
        self->unk_A59 = func_ov094_0229a39c();
        self->unk_A5A++;
    } else if (state == 8) {
        func_ov094_0229a99c(self, self->unk_A54, 0);
        self->unk_A59 = 0;
        self->unk_A5A++;
    } else if (state < 12) {
        self->unk_A59 = func_ov094_0229a39c();
        self->unk_A5A++;
    } else {
        func_ov094_0229a464();
        return 1;
    }
    return 0;
}
