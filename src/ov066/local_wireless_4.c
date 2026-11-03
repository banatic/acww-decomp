/* local_wireless_4: 2 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_02266bf4 @ 0x02266bf4, 0x88 bytes, ARM
 * func_ov066_02266b94 @ 0x02266b94, 0x60 bytes, ARM
 */

typedef void (*CallbackFunc)(void *arg);

struct UnkStruct_02266bf4 {
    int unk_00;
    char pad_04[0x30 - 0x04];
    CallbackFunc func;
    void *arg;
    char pad_38[0x3c - 0x38];
    unsigned int flags;
};

extern struct UnkStruct_02266bf4 *data_ov066_0226bdec;
extern int func_ov066_02267348(void);
extern void func_ov066_02266e70(void);
extern void func_ov066_02266b14(void *);
extern void func_ov066_02266ad4(void *);
extern void func_ov066_02266a8c(void *);
extern void func_ov066_02266a4c(void *);

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

void func_ov066_02266b94(void *p)
{
    switch (*(unsigned short *) p) {
        case 3:
            func_ov066_02266b14(p);
            break;
        case 4:
            func_ov066_02266ad4(p);
            break;
        case 5:
            func_ov066_02266a8c(p);
            break;
        case 6:
            func_ov066_02266a4c(p);
            break;
    }
    func_ov066_02266bf4();
}
