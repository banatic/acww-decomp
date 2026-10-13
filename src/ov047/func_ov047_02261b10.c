/* func_ov047_02261b10 @ 0x02261b10, 0x78 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fc6c(void *);
extern int func_02070dc0(void *);
extern int func_02070fa0(void *);
extern void func_0206844c(void *, void *, void *);

extern int data_021f38f8;
extern char data_ov047_02262fc0;

struct UnkStruct_02261b10 {
    char pad_00[0x40];
    void *unk_40;
};

void func_ov047_02261b10(struct UnkStruct_02261b10 *param)
{
    void *field40;
    void *addr;
    char byte;
    int ret;

    field40 = param->unk_40;
    if (func_0206fc6c(param) != 0) {
        byte = 0x13;
        addr = &data_021f38f8;
        ret = func_02070dc0(addr);
        if (ret == 0) {
            byte = 0x10;
        } else if (ret <= 0x0001e000) {
            byte = 0x11;
        } else if (ret <= 0x00046000) {
            byte = 0x12;
        } else if (func_02070fa0(addr) != 0) {
            byte = 0x49;
        }
        func_0206844c(field40, &byte, &data_ov047_02262fc0);
    }
}
