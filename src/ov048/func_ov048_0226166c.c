/* func_ov048_0226166c @ 0x0226166c, 0x4c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xb4];
    int unk_B4;
    char pad_B8[0x813 - 0xb4 - 4];
    unsigned char flag;
} UnkStruct_0226166c;

extern void func_02073044(UnkStruct_0226166c *p);
extern void func_020ec920(void);
extern int func_ov048_02260ea8(UnkStruct_0226166c *p);
extern void func_02073100(void);
extern int func_020eb844(void);
extern void func_ov048_022616b8(UnkStruct_0226166c *p, int n);

void func_ov048_0226166c(UnkStruct_0226166c *p)
{
    func_02073044(p);
    func_020ec920();
    if (func_ov048_02260ea8(p) != 0) {
        return;
    }
    func_02073100();
    if (func_020eb844() == 0) {
        return;
    }
    if (p->flag == 0) {
        func_ov048_022616b8(p, 0x13);
    } else {
        func_ov048_022616b8(p, p->unk_B4 + 1);
    }
}
