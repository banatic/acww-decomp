/* func_ov003_0220bf70 @ 0x0220bf70, 0x70 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct Other {
    unsigned char pad_00[8];
    int unk_08;
} Other;

typedef struct UnkStruct_0220bf70 {
    unsigned char pad_00[0x8];
    int unk_08;
    unsigned char pad_0C[0xec - 0xc];
    unsigned char sub;
    unsigned char pad_ED[0x10a - 0xed];
    unsigned char unk_10A;
    unsigned char pad_10B[0x12c - 0x10b];
    Other *unk_12C;
} UnkStruct_0220bf70;

extern void func_0203ee14(void *self, void *sub);
extern void func_020a8164(void *sub, void *data);
extern void func_02094fd4(void *local);
extern void func_0207cec0(void *data, int val);
extern int func_0208150c(void);
extern void func_02003618(int val, void *local);
extern void func_02068404(Other *other, int zero, void *local);
extern void func_02094fbc(void *local);

extern char data_ov003_022380f0;
extern char data_021e5a2c;

int func_ov003_0220bf70(UnkStruct_0220bf70 *self)
{
    struct {
        int unused;
        unsigned char local[0x24];
    } buf;
    char *p = (char *) self;

    if (self != 0) {
        p += 0xec;
    }
    func_0203ee14(self, p);

    func_020a8164((char *) &self->sub, &data_ov003_022380f0);

    self->unk_10A = 0;
    self->unk_12C->unk_08 = 1;

    func_02094fd4(buf.local);
    func_0207cec0(&data_021e5a2c, self->unk_08);
    func_02003618(func_0208150c(), buf.local);
    func_02068404(self->unk_12C, 0, buf.local);
    func_02094fbc(buf.local);

    return 1;
}
