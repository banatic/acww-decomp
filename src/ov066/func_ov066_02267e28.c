/* func_ov066_02267e28 @ 0x02267e28, 0xd0 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

typedef struct Obj1 {
    char pad_00[9];
    unsigned char unk_09;
} Obj1;

typedef struct Work {
    void *unk_00;
    void *unk_04;
    void *unk_08;
    int unk_0C;
    char sub_10[0x3c - 0x10];
    char sub_3c[0x6c - 0x3c];
    int unk_6C;
} Work;

extern Obj1 *data_ov066_0226bdec;
extern Work *data_ov066_0226bdf0;

void func_ov066_0226a7d8(void *);
void func_ov066_022668c4(void *);
void OS_CancelAlarm(void *);

void func_ov066_02267e28(void)
{
    int i = data_ov066_0226bdec->unk_09 - 1;
    int off;

    if (i >= 0) {
        off = i * 16;
        do {
            func_ov066_0226a7d8((char *) data_ov066_0226bdf0->unk_08 + off);
            off -= 16;
        } while (--i >= 0);
    }

    func_ov066_022668c4(data_ov066_0226bdf0->unk_08);
    func_ov066_022668c4(data_ov066_0226bdf0->unk_04);
    func_ov066_022668c4(data_ov066_0226bdf0->unk_00);

    data_ov066_0226bdf0->unk_6C = 0;
    data_ov066_0226bdf0->unk_0C &= ~1;

    OS_CancelAlarm(&data_ov066_0226bdf0->sub_3c);
    OS_CancelAlarm(&data_ov066_0226bdf0->sub_10);

    func_ov066_022668c4(data_ov066_0226bdf0);
    data_ov066_0226bdf0 = 0;
}
