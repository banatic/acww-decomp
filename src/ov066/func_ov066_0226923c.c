/* func_ov066_0226923c @ 0x0226923c, 0x60 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int func_ov066_02266e08(void);
extern int func_ov066_02268c90(void);
extern void func_ov066_02268f1c(void *arg);
extern void func_ov066_02268da4(void *arg);

struct data_s {
    unsigned char pad_00[0x1e];
    unsigned short flag;
};
extern struct data_s *data_ov066_0226bdf4;

void func_ov066_0226923c(void *arg)
{
    if (func_ov066_02266e08()) {
        return;
    }
    if (func_ov066_02268c90()) {
        return;
    }
    if (data_ov066_0226bdf4->flag == 0) {
        func_ov066_02268f1c(arg);
    } else {
        func_ov066_02268da4(arg);
    }
}
