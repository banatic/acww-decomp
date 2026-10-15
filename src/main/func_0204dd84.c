/* func_0204dd84 @ 0x0204dd84, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned char pad_0C[0x10];
    int unk_1C;
} UnkStruct_0204dd84;
extern void *data_021c9b34;
extern int func_02030ddc(unsigned int a, unsigned int b, int c, int d);
extern int func_02037e84(void *x);
extern int func_0203750c(void);
extern int func_020377d8(int a, void *g);
extern void func_02037ecc(void *x, int a, int b, int c);
void func_0204dd84(UnkStruct_0204dd84 *p)
{
    void *x;
    unsigned int z = 0;
    func_02030ddc(p->unk_04, p->unk_08, 0, p->unk_1C);
    if (p->unk_04 > z && p->unk_08 > z && p->unk_00 != 0) {
        x = p->unk_00;
    } else {
        x = 0;
    }
    if (x != 0) {
        int a = func_02037e84(x);
        void *g = data_021c9b34;
        func_0203750c();
        func_02037ecc(x, 0, func_020377d8(a, g), p->unk_1C);
    }
}
