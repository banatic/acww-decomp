/* func_ov066_0226686c @ 0x0226686c, 0x58 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    int unk_00;
    unsigned int unk_04;
    unsigned char pad_08[0x34];
    unsigned int unk_3C;
} Obj066;

extern volatile Obj066 *data_ov066_0226bdec;
extern void (*data_ov066_0226bde0)(int);

void func_ov066_0226686c(int arg)
{
    data_ov066_0226bdec->unk_04 = arg | 0x80;
    data_ov066_0226bdec->unk_3C &= ~0x800;
    if (data_ov066_0226bde0) {
        data_ov066_0226bde0(arg);
    }
}
