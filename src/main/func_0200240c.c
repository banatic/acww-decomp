/* func_0200240c @ 0x0200240c, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02001ec4(unsigned short *p0);
extern void func_02001ea8(unsigned int *arg0);
extern void func_02001e94(unsigned char *r0);
extern void func_02001c08(unsigned char param);
extern void func_02001c30(unsigned char param);

struct BigObj {
    unsigned char pad_00[0x10];
    unsigned char unk_10;
    unsigned char unk_11;
    unsigned short unk_12;
    unsigned char unk_14;
    unsigned char unk_15;
    unsigned char unk_16;
    unsigned char unk_17;
    unsigned char unk_18;
    unsigned char unk_19;
    unsigned char unk_1A;
    unsigned char unk_1B;
    unsigned char unk_1C;
    unsigned char unk_1D;
};
extern struct BigObj data_0213fe74;

struct Small2 {
    unsigned char pad_00[0x12];
    unsigned char unk_12;
    unsigned char pad_13;
    unsigned char unk_14;
};
extern struct Small2 data_0213fe94;

extern unsigned short data_0213fdf4[2];
extern unsigned short data_0213fdf8[2];
extern unsigned int data_0213fdfc[8];
extern unsigned int data_0213fe1c[8];
extern unsigned short data_0213fe3c[2];
extern unsigned short data_0213fe40[2];
extern unsigned int data_0213fe44[8];
extern unsigned int data_0213fe64[8];
extern unsigned char data_0213fe92[5];
extern unsigned char data_0213fe97[5];
extern unsigned char data_0213fe9c[5];
extern unsigned char data_0213fea1[5];

void func_0200240c(void)
{
    data_0213fe74.unk_14 = 0;
    data_0213fe74.unk_15 = 0;
    data_0213fe74.unk_18 = 0;
    data_0213fe74.unk_19 = 0;
    data_0213fe74.unk_1A = 0;
    data_0213fe74.unk_1B = 0;
    data_0213fe74.unk_1C = 0;
    data_0213fe74.unk_1D = 0;
    data_0213fe74.unk_16 = 0;
    data_0213fe74.unk_17 = 1;

    func_02001ec4(data_0213fdf4);
    func_02001ec4(data_0213fdf8);
    func_02001ea8(data_0213fdfc);
    func_02001ea8(data_0213fe1c);
    func_02001ec4(data_0213fe3c);
    func_02001ec4(data_0213fe40);
    func_02001ea8(data_0213fe44);
    func_02001ea8(data_0213fe64);
    func_02001e94(data_0213fe92);
    func_02001e94(data_0213fe97);
    func_02001e94(data_0213fe9c);
    func_02001e94(data_0213fea1);

    data_0213fe74.unk_10 = 0;
    data_0213fe74.unk_11 = 0xff;
    data_0213fe74.unk_12 = 0xff;

    data_0213fe94.unk_12 = 0;
    data_0213fe94.unk_14 = 0;

    func_02001c08(0);
    func_02001c30(1);
}
