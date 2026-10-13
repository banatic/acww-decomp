/* func_020a3bc0 @ 0x020a3bc0, 0x2b4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a3bc0_2 {
    char pad_00[0xa1];
    unsigned char state;
    char pad_A2[0xcc - 0xa2];
    int unk_CC;
    char pad_D0[0xd6 - 0xd0];
    unsigned char unk_D6;
    char pad_D7[0xd8 - 0xd7];
    unsigned char unk_D8;
    unsigned char unk_D9;
    char pad_DA[0xe4 - 0xda];
    unsigned char unk_E4;
};

struct UnkStruct_020a3bc0 {
    char pad_00[0x6c];
    unsigned char unk_6C;
};

extern struct UnkStruct_020a3bc0 *data_020ccf94;
extern unsigned char data_021f3c1c;

extern int func_020740dc(void);
extern int func_02073fdc(int a);
extern void func_02074078(void);
extern int func_020a6ed0(void);
extern int func_020a6cc4(void);
extern void func_020a0340(struct UnkStruct_020a3bc0_2 *o, unsigned char *p, int a, int b, int c);
extern void func_020a7394(int a, int b, int c, int d, int e);
extern void func_020738f4(struct UnkStruct_020a3bc0 *g, unsigned char v);
extern void func_02073de0(struct UnkStruct_020a3bc0 *g, int a, int b);
extern void func_02075104(int a);
extern int func_020760bc(unsigned short m);
extern int func_02077690(int a);
extern int func_02075d40(unsigned short m);
extern int func_02075d9c(unsigned char *p, unsigned short m);
extern int func_020759e0(int a);
extern void func_020a003c(int a, int b);
extern int func_020a0030(int a);
extern void DC_FlushAll(void);
extern int func_02075fc4(unsigned char *p, unsigned short m);
extern int func_02075b14(unsigned short m);
extern int func_02073044(void);
extern int func_020ebf70(int a);
extern void func_02073d74(struct UnkStruct_020a3bc0 *g, int a);
extern void func_0209fc40(int a);

void func_020a3bc0(struct UnkStruct_020a3bc0_2 *self)
{
    struct UnkStruct_020a3bc0 *g;

    switch (self->state) {
        case 0:
            if (func_02073fdc(func_020740dc() | (1 << func_020a6ed0()))) {
                func_02074078();
                return;
            }
            if (!func_020a6cc4()) {
                return;
            }
            self->state = 1;
            return;

        case 1:
        case 2:
            if (func_02073fdc(func_020740dc() | (1 << func_020a6ed0()))) {
                func_02074078();
                return;
            }
            func_020a0340(self, &self->state, 1, 0xd, 0x2f);
            if (self->state <= 2) {
                return;
            }
            func_020a7394(data_021f3c1c, 0xc, 1, 0, 7);
            g = data_020ccf94;
            func_020738f4(g, (unsigned char) (g->unk_6C + 1));
            func_02073de0(g, data_021f3c1c, 1);
            func_02075104(data_021f3c1c);
            return;

        case 3:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            if (!func_020760bc((unsigned short) (1 << data_021f3c1c))) {
                return;
            }
            self->state = 4;
            return;

        case 4:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            if (!func_02077690(data_021f3c1c)) {
                return;
            }
            self->state = 5;
            return;

        case 5:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            if (!func_02075d40((unsigned short) (1 << data_021f3c1c))) {
                return;
            }
            self->unk_D8 = 0;
            self->state = 6;
            return;

        case 6:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            if (!func_02075d9c(&self->unk_D8, (unsigned short) (1 << data_021f3c1c))) {
                return;
            }
            self->state = 7;
            return;

        case 7:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            if (!func_020759e0(data_021f3c1c)) {
                return;
            }
            func_020a003c(self->unk_CC, 1);
            self->unk_D8 = 0;
            self->state = 8;
            return;

        case 8:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            if (!func_020a0030(self->unk_CC)) {
                return;
            }
            DC_FlushAll();
            if (!func_02075fc4(&self->unk_D8, (unsigned short) (1 << data_021f3c1c))) {
                return;
            }
            self->state = 9;
            return;

        case 9:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            if (!self->unk_D9) {
                return;
            }
            if (!func_02075b14((unsigned short) (1 << data_021f3c1c))) {
                return;
            }
            self->state = 0xa;
            return;

        case 10:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            if (!func_020ebf70(func_02073044())) {
                return;
            }
            if (!self->unk_E4) {
                return;
            }
            func_02073d74(data_020ccf94, 2);
            self->unk_D6 = 1;
            func_0209fc40(data_021f3c1c);
            self->state = 0xb;
            return;
    }
}
