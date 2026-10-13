/* func_ov048_022619b0 @ 0x022619b0, 0x40 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov048_022635f4(void *ptr, int n);
extern char func_ov048_022609fc(void *obj);
extern void func_0206844c(void *dst, char *buf, int data);
extern int data_ov048_02263d20;

typedef struct {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0xb8 - 0x44];
    void *unk_B8;
} UnkStruct_022619b0;

typedef struct {
    char pad_00[0x14];
    int unk_14;
} PType;

void func_ov048_022619b0(UnkStruct_022619b0 *obj, int mode)
{
    PType *p = obj->unk_40;
    if (mode == 0) {
        p->unk_14 = 0;
        func_ov048_022635f4(obj->unk_B8, 0xe);
    } else if (mode == 1) {
        char buf[8];
        buf[0] = func_ov048_022609fc(obj);
        func_0206844c(p, buf, data_ov048_02263d20);
    }
}
