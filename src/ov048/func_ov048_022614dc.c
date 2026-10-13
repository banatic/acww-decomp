/* func_ov048_022614dc @ 0x022614dc, 0x38 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

struct FieldStruct {
    char pad_00[0xb4];
    int unk_B4;
};

extern int func_ov048_022614ac(void *);
extern void func_ov048_022616b8(void *, int);
extern void func_020eb9fc(void);
extern int func_0209fe1c(void);

void func_ov048_022614dc(void *arg)
{
    if (func_ov048_022614ac(arg) != 0) {
        func_020eb9fc();
        func_ov048_022616b8(arg, ((struct FieldStruct *) arg)->unk_B4 + 1);
    } else if (func_0209fe1c() != 0) {
        func_ov048_022616b8(arg, ((struct FieldStruct *) arg)->unk_B4 + 1);
    }
}
