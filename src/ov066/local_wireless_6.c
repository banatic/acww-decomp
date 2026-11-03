/* local_wireless_6: 2 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_0226760c @ 0x0226760c, 0x30 bytes, ARM
 * func_ov066_02267530 @ 0x02267530, 0xdc bytes, ARM
 */

typedef struct Node {
    int unk_00;
    int value;
} Node;

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
    unsigned char unk_0B;
    unsigned char unk_0C;
    unsigned char unk_0D;
    unsigned int unk_10;
    unsigned char pad_14[1];
    unsigned char unk_15;
    unsigned char unk_16;
    unsigned char pad_17[25];
    unsigned int unk_30;
    unsigned int unk_34;
    unsigned int unk_38;
    unsigned int unk_3C;
} Ov66Struct;

extern int OS_DisableInterrupts(void);
extern unsigned int OS_RestoreInterrupts(int state);
extern Node *data_ov066_0226bdec;

int func_ov066_0226760c(void)
{
    int result = 0;
    int state = OS_DisableInterrupts();

    if (data_ov066_0226bdec != 0) {
        result = data_ov066_0226bdec->value;
    }
    OS_RestoreInterrupts(state);
    return result;
}

void func_ov066_02267530(unsigned char arg0)
{
    (*(Ov66Struct * *) &data_ov066_0226bdec)->unk_00 = 7;
    (*(Ov66Struct * *) &data_ov066_0226bdec)->unk_04 = 1;
    (*(Ov66Struct * *) &data_ov066_0226bdec)->unk_08 = 0xfe;
    (*(Ov66Struct * *) &data_ov066_0226bdec)->unk_09 = 1;
    (*(Ov66Struct * *) &data_ov066_0226bdec)->unk_0A = 0;
    (*(Ov66Struct * *) &data_ov066_0226bdec)->unk_0B = 0;
    (*(Ov66Struct * *) &data_ov066_0226bdec)->unk_0C = 0;
    (*(Ov66Struct * *) &data_ov066_0226bdec)->unk_0D = arg0;
    (*(Ov66Struct * *) &data_ov066_0226bdec)->unk_10 = 0;
    (*(Ov66Struct * *) &data_ov066_0226bdec)->unk_15 = 0;
    (*(Ov66Struct * *) &data_ov066_0226bdec)->unk_16 = 0;
    (*(Ov66Struct * *) &data_ov066_0226bdec)->unk_30 = 0;
    (*(Ov66Struct * *) &data_ov066_0226bdec)->unk_34 = 0;
    (*(Ov66Struct * *) &data_ov066_0226bdec)->unk_38 = 0;
    (*(Ov66Struct * *) &data_ov066_0226bdec)->unk_3C &= ~0x800;
    (*(Ov66Struct * *) &data_ov066_0226bdec)->unk_3C &= ~0x400;
    (*(Ov66Struct * *) &data_ov066_0226bdec)->unk_3C &= ~0x1000;
    (*(Ov66Struct * *) &data_ov066_0226bdec)->unk_3C &= ~0x800;
}
