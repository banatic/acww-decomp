/* func_ov066_02268410 @ 0x02268410, 0x48 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern void func_ov066_02266950(void);
extern void func_ov066_02267cb0(int value);
extern void func_ov066_0226686c(int value);

struct UnkStruct_02268410 {
    unsigned char pad_00[2];
    unsigned short flag;
};

struct TargetStruct {
    unsigned int pad_00;
    int unk_04;
};

extern struct TargetStruct *data_ov066_0226bdec;

void func_ov066_02268410(struct UnkStruct_02268410 *self)
{
    func_ov066_02266950();
    if (self->flag == 0) {
        struct TargetStruct *p = data_ov066_0226bdec;
        p->unk_04 = 4;
        func_ov066_02267cb0(100);
        return;
    } else {
        func_ov066_0226686c(self->flag);
        return;
    }
}
