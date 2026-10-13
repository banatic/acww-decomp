/* func_ov109_0229cd10 @ 0x0229cd10, 0x8c bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

extern void func_ov002_02208098(void *self, int a);
extern int func_ov109_0229cbd4(void *self, int a);
extern int func_ov109_0229cb9c(void *self, int a);
extern void func_ov002_02207cf8(char *p);
extern void func_ov002_02207d00(char *p);
extern int func_ov109_0229cae0(void *self, int a);
extern void func_ov094_022999cc(void);

struct Context {
    char pad_00[0x218c];
    char sub[0x830];
    int unk_29BC;
    int unk_29C0;
    char pad_29C4[0xC];
    unsigned char unk_29D0;
    unsigned char unk_29D1;
    char pad_29D2[7];
    unsigned char unk_29D9;
};

void func_ov109_0229cd10(struct Context *self, int arg)
{
    unsigned char g1;
    unsigned char g2;

    self->unk_29D0 = arg;
    func_ov002_02208098(self, 1);
    g1 = data_021f6c58;
    g2 = data_021f6c54;

    self->unk_29BC = func_ov109_0229cbd4(self, self->unk_29D0) - g1;
    self->unk_29C0 = func_ov109_0229cb9c(self, self->unk_29D0) - g2;
    self->unk_29D1 = arg;
    func_ov002_02207cf8(self->sub);
    func_ov002_02207d00(self->sub);
    self->unk_29D9 = 2;
    if (func_ov109_0229cae0(self, arg) == 0) {
        func_ov094_022999cc();
    }
}
