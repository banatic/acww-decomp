/* local_host: 2 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_0226848c @ 0x0226848c, 0x38 bytes, ARM
 * func_ov066_02268458 @ 0x02268458, 0x34 bytes, ARM
 */

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
} UnkStruct_02268458;

extern int WM_SetEntry(void (*callback)(void *), int arg);
extern void func_ov066_0226686c(int status);
extern int func_ov066_02266e08(void);

void func_ov066_02268458(UnkStruct_02268458 *self);

void func_ov066_0226848c(int arg)
{
    int status = WM_SetEntry((void (*)(void *)) func_ov066_02268458, arg);
    if (status == 2) {
        return;
    }
    func_ov066_0226686c(status);
}

void func_ov066_02268458(UnkStruct_02268458 *self)
{
    if (func_ov066_02266e08() != 0) {
        return;
    }
    if (self->unk_02 == 0) {
        return;
    }
    func_ov066_0226686c((unsigned short) self->unk_02);
    return;
}
