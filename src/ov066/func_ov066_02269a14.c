/* func_ov066_02269a14 @ 0x02269a14, 0x90 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

typedef struct Unk9A14 {
    char pad_00[0x93];
    unsigned char unk_93;
    unsigned char unk_94;
    unsigned char unk_95;
    char pad_96[2];
    unsigned short unk_98;
    char pad_9A[2];
    void (*fn0x9c)(void);
    char pad_A0[0x20];
    unsigned int fl0xc0;
} Unk9A14;

extern Unk9A14 *data_ov066_0226bdf4;
extern void func_ov066_02267e00(int);
extern void func_ov066_0226929c(void);
extern void func_ov066_0226a224(void);

void func_ov066_02269a14(void)
{
    func_ov066_02267e00(0);
    data_ov066_0226bdf4->fl0xc0 &= ~4;
    data_ov066_0226bdf4->fn0x9c();
    data_ov066_0226bdf4->fl0xc0 &= ~1;
    data_ov066_0226bdf4->fl0xc0 &= ~2;
    data_ov066_0226bdf4->unk_93 = 0;
    data_ov066_0226bdf4->unk_94 = 0;
    data_ov066_0226bdf4->unk_95 = 0;
    data_ov066_0226bdf4->unk_98 = 0;
    func_ov066_0226929c();
    func_ov066_0226a224();
}
