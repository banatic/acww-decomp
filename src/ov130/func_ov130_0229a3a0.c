/* func_ov130_0229a3a0 @ 0x0229a3a0, 0x50 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov130_0229a3f0(unsigned char);
extern int func_ov130_022999c0(void *);
extern void func_0207094c(int, unsigned char, unsigned char);
extern void func_02070adc(int, int, int, int, int, int, int);
extern void func_02070a04(int, int, int);
extern const unsigned char data_ov130_0229a7fc[];

struct UnkStruct_0229a3a0 {
    char pad_00[7];
    unsigned char unk_07;
    char pad_08;
    unsigned char unk_09;
};

void func_ov130_0229a3a0(struct UnkStruct_0229a3a0 *p)
{
    int r4;
    func_ov130_0229a3f0(p->unk_09);
    r4 = func_ov130_022999c0(p);
    func_0207094c(r4, data_ov130_0229a7fc[p->unk_07], p->unk_07);
    func_02070adc(r4, 8, 0x14c, 14, 15, 0, 0);
    func_02070a04(r4, 1, 0);
}
