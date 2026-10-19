/* func_ov134_0229a3e4 @ 0x0229a3e4, 0x68 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200467c(int);
extern void func_02001b6c(int);
extern void func_02001d74(int, int);
extern int func_02002d8c(int);
extern void func_02001d00(int);
extern void func_ov134_0229b6dc(void *);
extern void func_ov134_022995a0(void *, int);

typedef struct {
    int unk_00;
    char pad_04[0x7c];
    int unk_80;
    char pad_84[0x20];
    unsigned char unk_A4;
    char pad_A5[4];
    unsigned char unk_A9;
    char pad_AA[1];
    unsigned char unk_AB;
    char pad_AC[1];
    unsigned char unk_AD;
    char pad_AE[1];
    unsigned char unk_AF;
} UnkStruct_0229a3e4;

void func_ov134_0229a3e4(UnkStruct_0229a3e4 *p)
{
    func_0200467c(0x29);
    p->unk_A9 = 3;
    p->unk_AF = 3;
    func_02001b6c(1);
    func_02001d74(0x1f, 1);
    func_02001d00(~func_02002d8c(p->unk_A4) & 0x1f);
    func_ov134_0229b6dc(p);
    p->unk_80 = p->unk_AB + (p->unk_AD << 4) - p->unk_00;
    func_ov134_022995a0(p, 4);
}
