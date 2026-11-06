/* star_designer_3: 3 functions, module ov129
 * mwccarm 1.2/base -O4,s
 * func_ov129_0229d360 @ 0x0229d360, 0x20 bytes, Thumb
 * func_ov129_0229d2d0 @ 0x0229d2d0, 0x90 bytes, Thumb
 * func_ov129_0229d268 @ 0x0229d268, 0x68 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x94];
    unsigned int unk_94;
    unsigned int unk_98;
    unsigned char pad_9C[0xa4 - 0x9c];
    unsigned short unk_A4;
    unsigned short unk_A6;
    unsigned short unk_A8;
    unsigned short unk_AA;
    unsigned char pad_AC[0xae - 0xac];
    unsigned char unk_AE;
    unsigned char pad_AF[0xb0 - 0xaf];
    unsigned char unk_B0;
    unsigned char pad_B1[0xb3 - 0xb1];
    unsigned char unk_B3;
    unsigned char unk_B4;
} UnkStruct_0229d2d0;

extern int func_0206fe60(void);
extern int func_ov129_0229d3e0(int);
extern int func_ov129_0229d380(int);
extern void func_ov127_0229a0bc(void *ptr);
extern void func_ov129_0229c118(UnkStruct_0229d2d0 *self);
extern void func_ov129_0229c094(UnkStruct_0229d2d0 *self);
extern void func_ov129_0229bfbc(UnkStruct_0229d2d0 *self);
extern int func_ov004_0222be7c(void);
extern void func_0203584c(char *ptr);
extern char *data_021c526c;
extern void func_020b1774(void *);
extern void func_ov127_02299e5c(void *);
extern void func_ov002_0220af74(void *);
extern int func_02095904(void);
extern void func_02035834(void *);
extern int func_02002c6c(void *, int, int, int, int, int);
extern int data_ov129_0229dc98;
extern int data_021fbe94;

int func_ov129_0229d360(int param)
{
    int result;
    if (func_0206fe60() != 0) {
        result = func_ov129_0229d3e0(param);
    } else {
        result = func_ov129_0229d380(param);
    }
    return result;
}

void func_ov129_0229d2d0(UnkStruct_0229d2d0 *self)
{
    self->unk_A4 = 0;
    func_ov127_0229a0bc((char *) self + 0x734);
    self->unk_94 = 0x80;
    self->unk_98 = 0x60;
    self->unk_AE = 4;
    self->unk_A6 = 0xffff;
    self->unk_A8 = 0xffff;
    self->unk_B4 = 0;
    func_ov129_0229c118(self);
    func_ov129_0229c094(self);
    self->unk_B0 = 0xff;
    self->unk_AA = 0xffff;
    self->unk_B3 = 0xff;
    func_ov129_0229bfbc(self);
    func_ov004_0222be7c();
    func_0203584c(data_021c526c + 0x2f0);
}

void func_ov129_0229d268(void *obj)
{
    func_020b1774((char *) obj + 0x404);
    func_ov127_02299e5c((char *) obj + 0x734);
    func_ov002_0220af74((char *) obj + 0x1d4);
    func_02095904();
    func_02035834((char *) (*(void **) &data_021c526c) + 0x2f0);
    func_02002c6c(&data_ov129_0229dc98, data_021fbe94, 3, 0, 0x10, 0x10);
}
