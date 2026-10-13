/* func_ov066_02267cb0 @ 0x02267cb0, 0x104 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern struct UnkStruct_02267cb0 {
    unsigned char pad_00[0x3c];
    struct {
        unsigned int : 3;
        signed int flag : 1;
        unsigned int : 28;
    } bits;
} *data_ov066_0226bdec;
extern struct UnkStruct_02267cb0_2 {
    unsigned char pad_00[0x95];
    unsigned char unk_95;
} *data_ov066_0226bdf4;
extern struct UnkStruct_02267cb0_3 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
} *data_ov066_0226bdf0;

extern void func_ov066_0226a3b0(int);
extern void func_ov066_0226a2e8(int, int);
extern void func_ov066_02267e00(int);
extern void OS_CancelAlarm(void *);
extern void OS_SetAlarm(void *, long long, void (*)(void), int);
extern void func_ov066_02267c74(void);
extern void func_ov066_02267c0c(void);

void func_ov066_02267cb0(int arg0)
{
    if (data_ov066_0226bdec->bits.flag != 0) {
        func_ov066_0226a3b0(data_ov066_0226bdf0->unk_08 + ((int) data_ov066_0226bdf4->unk_95 << 4));
    } else {
        func_ov066_0226a2e8(data_ov066_0226bdf0->unk_08 + ((int) data_ov066_0226bdf4->unk_95 << 4), 500);
        func_ov066_02267e00(0);
    }

    data_ov066_0226bdf0->unk_0C |= 2;
    data_ov066_0226bdf0->unk_0C &= ~1;

    if (arg0 != 0) {
        int q;

        OS_CancelAlarm((char *) data_ov066_0226bdf0 + 0x10);
        q = (arg0 * 33514) / 64;
        OS_SetAlarm((char *) data_ov066_0226bdf0 + 0x10, (long long) q, func_ov066_02267c74, 0);
    }

    func_ov066_02267c0c();
}
