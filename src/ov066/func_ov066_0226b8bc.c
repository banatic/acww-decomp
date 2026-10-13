/* func_ov066_0226b8bc @ 0x0226b8bc, 0x50 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0226b8bc {
    unsigned char pad_00[4];
    unsigned char b0 : 3;
    unsigned char b3 : 1;
    unsigned char b4 : 4;
} UnkStruct_0226b8bc;
typedef struct UnkStruct_0226b8bc_2 {
    unsigned char pad_00[4];
    unsigned long unk_04;
} UnkStruct_0226b8bc_2;
extern UnkStruct_0226b8bc *data_ov066_0226be08;
extern UnkStruct_0226b8bc_2 *data_ov066_0226bdec;
int func_ov066_0226b8bc(void)
{
    int result = 0;
    UnkStruct_0226b8bc *q = data_ov066_0226be08;
    if (q != 0) {
        unsigned long st = data_ov066_0226bdec->unk_04;
        if (st != 10) {
            if (st != 11) {
                return result;
            }
        }
        if (!q->b3) {
            result = 1;
        } else {
            result = 0;
        }
    }
    return result;
}
