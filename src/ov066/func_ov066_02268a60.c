/* func_ov066_02268a60 @ 0x02268a60, 0x70 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

typedef struct UnkStruct_02268a60_2 {
    char pad_00[2];
    unsigned short unk_02;
} UnkStruct_02268a60_2;

typedef struct UnkStruct_02268a60 {
    char pad_00[0xc0];
    int : 3;
    int b : 1;
} UnkStruct_02268a60;

extern int *data_ov066_0226bdec;
extern UnkStruct_02268a60 *data_ov066_0226bdf4;

extern int func_ov066_02266e08(void);
extern void func_ov066_02269dcc(void);
extern void func_ov066_02266bf4(void);
extern void func_ov066_0226686c(int status);

void func_ov066_02268a60(UnkStruct_02268a60_2 *self)
{
    if (func_ov066_02266e08() != 0) {
        return;
    }
    if (self->unk_02 == 0) {
        *(data_ov066_0226bdec + 1) = 4;
        if (data_ov066_0226bdf4->b) {
            func_ov066_02269dcc();
        }
        func_ov066_02266bf4();
        return;
    } else {
        func_ov066_0226686c(self->unk_02);
        return;
    }
}
