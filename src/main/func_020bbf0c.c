/* func_020bbf0c @ 0x020bbf0c, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209def4(void *ptr);
extern void func_020bc110(int a, int b, int c, int d);
extern void func_020bbf9c(int a, int b, int c, int d);
extern void func_020bc078(int a, int b, int c, int d);
extern void func_020b68d4(int a);
extern void func_02002e48(int a);
extern void func_02002e3c(unsigned short a);
extern int func_02065604(void);
extern void NNS_G3dGlbMaterialColorSpecEmi(int a, unsigned short b, int c);

extern int data_021f6cd8;
extern struct global_struct_type {
    char pad_00[6];
    unsigned short unk_06;
} data_021f7270;

struct local_data_type {
    unsigned short unk_00;
    unsigned char unk_02;
    unsigned char unk_03;
    unsigned short unk_04;
    unsigned short unk_06;
};

void func_020bbf0c(int p1, int p2)
{
    struct local_data_type data;
    unsigned char r4;
    int r7;

    func_0209def4(&data.unk_02);
    r4 = data.unk_03;
    r7 = (unsigned int) (r4 + 1) % 24;
    func_020bc110(p1, p2, r4, r7);
    func_020bbf9c(p1, p2, r4, r7);
    func_020bc078(p1, p2, r4, r7);

    if (data_021f6cd8) {
        func_020b68d4(0);
        func_02002e48(0x1c2);
        data.unk_04 = data_021f7270.unk_06;
        func_02002e3c(data.unk_04);
    }

    data.unk_00 = (unsigned short) func_02065604();
    data.unk_06 = data.unk_00;
    NNS_G3dGlbMaterialColorSpecEmi(0, data.unk_06, 0);
}
