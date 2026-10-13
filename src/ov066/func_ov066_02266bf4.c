/* func_ov066_02266bf4 @ 0x02266bf4, 0x88 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern struct UnkStruct_02266bf4 *data_ov066_0226bdec;
extern int func_ov066_02267348(void);
extern void func_ov066_02266e70(void);

typedef void (*CallbackFunc)(void *arg);

struct UnkStruct_02266bf4 {
    int unk_00;
    char pad_04[0x30 - 0x04];
    CallbackFunc func;
    void *arg;
    char pad_38[0x3c - 0x38];
    unsigned int flags;
};

void func_ov066_02266bf4(void)
{
    if (func_ov066_02267348() != 0) {
        data_ov066_0226bdec->flags &= ~0x800;
        if (data_ov066_0226bdec->func) {
            data_ov066_0226bdec->func(data_ov066_0226bdec->arg);
            if (data_ov066_0226bdec) {
                data_ov066_0226bdec->func = 0;
            }
        }
        if (data_ov066_0226bdec) {
            data_ov066_0226bdec->unk_00 = 7;
        }
    } else {
        func_ov066_02266e70();
    }
}
