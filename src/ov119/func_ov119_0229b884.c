/* func_ov119_0229b884 @ 0x0229b884, 0x60 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022090e4(void *, int);
extern int func_ov002_02208ae4(void *);
extern int func_ov002_02208ad8(void *, unsigned char);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_0208e4c0(void *, int);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);

typedef struct {
    unsigned char pad_00[0xAD];
    unsigned char unk_AD;
    unsigned char unk_AE;
    unsigned char pad_AF[0x2D];
    unsigned char unk_DC[1];
    unsigned char pad_DD[0xDA8 - 0xDC - 1];
    unsigned char unk_DA8[1];
} UnkStruct_0229b884;

int func_ov119_0229b884(UnkStruct_0229b884 *p)
{
    int v, w;
    p->unk_AD = 10;
    p->unk_AE = func_ov002_022090e4(&p->unk_DC, 1);
    v = func_ov002_02208ae4(&p->unk_DC);
    w = func_ov002_02208ad8(&p->unk_DC, p->unk_AE);
    func_ov002_0220a0b4(&p->unk_DA8, v, w);
    func_0208e4c0(&p->unk_DA8, 8);
    return (int) func_ov002_02208098(p, 0xB);
}
