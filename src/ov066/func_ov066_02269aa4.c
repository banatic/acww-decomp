/* func_ov066_02269aa4 @ 0x02269aa4, 0xe4 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_02269aa4;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
} UnkStruct_02269aa4_2;

extern UnkStruct_02269aa4 *data_ov066_0226bdec;   // 0x0226bdec
extern UnkStruct_02269aa4_2 *data_ov066_0226bdf4; // 0x0226bdf4

extern int WM_Finish(void); // 0x0212073c
extern void func_ov066_02267e28(void);
extern void func_ov066_022668c4(int arg);
extern void func_ov066_0226686c(int arg);

void func_ov066_02269aa4(void)
{
    if (data_ov066_0226bdec->unk_04 == 2) {
        if (WM_Finish() != 0) {
            return;
        }
        func_ov066_02267e28();
        func_ov066_022668c4(data_ov066_0226bdf4->unk_14);
        func_ov066_022668c4(data_ov066_0226bdf4->unk_10);
        func_ov066_022668c4(data_ov066_0226bdf4->unk_0C);
        func_ov066_022668c4(data_ov066_0226bdf4->unk_08);
        func_ov066_022668c4(data_ov066_0226bdf4->unk_00);
        func_ov066_022668c4(data_ov066_0226bdf4->unk_04);
        func_ov066_022668c4((int) data_ov066_0226bdf4);
        data_ov066_0226bdf4 = 0;
        data_ov066_0226bdec->unk_04 = 1;
    } else {
        func_ov066_0226686c(0x44);
    }
}
