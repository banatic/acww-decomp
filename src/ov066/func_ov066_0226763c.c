/* func_ov066_0226763c @ 0x0226763c, 0x50 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    unsigned char pad_00[2];
    unsigned short field;
} Arg;

typedef struct {
    unsigned int pad_00;
    unsigned int field;
} Target;

extern int func_ov066_02266e08(void);
extern void func_ov066_02266bf4(void);
extern void func_ov066_0226686c(int status);
extern Target *data_ov066_0226bdec;

void func_ov066_0226763c(Arg *arg)
{
    if (func_ov066_02266e08() != 0) {
        return;
    }
    if (arg->field == 0) {
        data_ov066_0226bdec->field = 4;
        func_ov066_02266bf4();
        return;
    } else {
        func_ov066_0226686c(arg->field);
        return;
    }
}
