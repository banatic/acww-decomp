/* func_ov066_02266a4c @ 0x02266a4c, 0x40 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#pragma arm
typedef struct UnkStruct_02266a4c {
    unsigned short unk_00;
    unsigned short unk_02;
    int unk_04;
} UnkStruct_02266a4c;

extern UnkStruct_02266a4c *data_ov066_0226bdec;
extern void func_ov066_0226686c(void);

void func_ov066_02266a4c(UnkStruct_02266a4c *arg)
{
    if (arg->unk_02 == 0) {
        data_ov066_0226bdec->unk_04 = 3;
        return;
    }
    func_ov066_0226686c();
}
