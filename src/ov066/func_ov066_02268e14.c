/* func_ov066_02268e14 @ 0x02268e14, 0x88 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
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

extern struct data_a *data_ov066_0226bdec;
extern struct data_b *data_ov066_0226bdf4;
extern void func_ov066_022695ac(int a, int b);
extern void func_ov066_02266e64(void);
extern void func_ov066_02266800(int a, int b);

void func_ov066_02268e14(void *self)
{
    data_ov066_0226bdec->unk_04 = 4;
    data_ov066_0226bdf4->func_0x9c();

    if (data_ov066_0226bdec->flag) {
        func_ov066_022695ac(0, 0);
    }

    if (!data_ov066_0226bdf4->flag) {
        func_ov066_02266e64();
    }

    func_ov066_02266800(2, 0);
}
