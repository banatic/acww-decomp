/* func_ov066_02269b88 @ 0x02269b88, 0xa0 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern void *func_ov066_02266908(int, int);
extern void func_ov066_022668c4(void *);
extern void func_ov066_02269c28(void);
extern int WM_Init(void *, unsigned char);

typedef struct {
    int pad_00;
    void *unk_04;
} UnkStruct_02269b88;

typedef struct {
    char pad_00[13];
    unsigned char unk_0D;
} OtherStruct;

extern UnkStruct_02269b88 *data_ov066_0226bdf4;
extern OtherStruct *data_ov066_0226bdec;

void func_ov066_02269b88(void)
{
    if (data_ov066_0226bdf4) {
        return;
    }

    data_ov066_0226bdf4 = (UnkStruct_02269b88 *) func_ov066_02266908(0xc4, 4);
    data_ov066_0226bdf4->unk_04 = (void *) func_ov066_02266908(0xf00, 0x20);

    if (WM_Init(data_ov066_0226bdf4->unk_04, data_ov066_0226bdec->unk_0D) == 0) {
        func_ov066_02269c28();
        return;
    }

    func_ov066_022668c4(data_ov066_0226bdf4->unk_04);
    return;
}
