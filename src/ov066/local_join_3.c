/* local_join_3: 3 functions, module ov066
 * mwccarm 1.2/base -O4,s
 * func_ov066_02268ea0 @ 0x02268ea0, 0x34 bytes, ARM
 * func_ov066_02268e9c @ 0x02268e9c, 0x4 bytes, ARM
 * func_ov066_02268e14 @ 0x02268e14, 0x88 bytes, ARM
 */

struct data_a {
    int unk_00;
    int unk_04;
    char pad0[0x34];
    int unk0 : 8;
    int flag : 1;
    int unk1 : 23;
};

struct data_b {
    char pad0[0x9c];
    void (*func_0x9c)(void);
    char pad_A0[0x20];
    int unk0 : 2;
    int flag : 1;
    int unk1 : 29;
};

extern unsigned int data_ov066_0226bdec;
extern unsigned int data_ov066_0226bdf4;
extern void func_ov066_022686f0(void);
extern void func_ov066_022695ac(int a, int b);
extern void func_ov066_02266e64(void);
extern void func_ov066_02266800(int a, int b);

void func_ov066_02268ea0(unsigned short *param0)
{
    unsigned int *r1;
    unsigned int *r2;
    unsigned short *r0;

    r1 = (unsigned int *) &data_ov066_0226bdec;
    r2 = (unsigned int *) *r1;
    r2[1] = 9;
    r1 = (unsigned int *) &data_ov066_0226bdf4;
    r0 = (unsigned short *) *r1;
    r0[15] = param0[5];
    func_ov066_022686f0();
}

void func_ov066_02268e9c(void *self) {}

void func_ov066_02268e14(void *self)
{
    (*(struct data_a * *) &data_ov066_0226bdec)->unk_04 = 4;
    (*(struct data_b * *) &data_ov066_0226bdf4)->func_0x9c();

    if ((*(struct data_a * *) &data_ov066_0226bdec)->flag) {
        func_ov066_022695ac(0, 0);
    }

    if (!(*(struct data_b * *) &data_ov066_0226bdf4)->flag) {
        func_ov066_02266e64();
    }

    func_ov066_02266800(2, 0);
}
