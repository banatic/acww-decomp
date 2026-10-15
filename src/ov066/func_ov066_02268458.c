/* func_ov066_02268458 @ 0x02268458, 0x34 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
} UnkStruct_02268458;

extern int func_ov066_02266e08(void);
extern void func_ov066_0226686c(unsigned short v);

void func_ov066_02268458(UnkStruct_02268458 *self)
{
    if (func_ov066_02266e08() != 0) {
        return;
    }
    if (self->unk_02 == 0) {
        return;
    }
    func_ov066_0226686c(self->unk_02);
    return;
}
