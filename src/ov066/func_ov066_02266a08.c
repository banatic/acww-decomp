/* func_ov066_02266a08 @ 0x02266a08, 0x44 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    unsigned char pad_00[0x3c];
    unsigned long unk_3C;
} UnkStruct_02266a08;

extern UnkStruct_02266a08 *data_ov066_0226bdec;

extern int WM_Reset(void);
extern void func_ov066_0226686c(int mode);

void func_ov066_02266a08(void)
{
    int mode = WM_Reset();
    data_ov066_0226bdec->unk_3C |= 0x400;
    if (mode == 2) {
        return;
    }
    func_ov066_0226686c(mode);
}
