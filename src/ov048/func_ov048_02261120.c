/* func_ov048_02261120 @ 0x02261120, 0x80 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02261120 {
    char pad_00[0x40];
    void *unk_40;
} UnkStruct_02261120;

extern void func_02068440(void *ptr);
extern void func_02073100(void);
extern int func_020ec49c(void);
extern void func_ov048_02262378(UnkStruct_02261120 *p);
extern int func_020984e8(void);
extern int func_0209985c(int object);
extern void func_0209fd54(void);
extern void func_0209fcd8(void);
extern void func_0209fc60(void);
extern int func_ov048_02262658(void);
extern void func_020a01f8(void);
extern int func_020a1518(void);
extern void func_0206844c(void *ptr, char *byte, int value);
extern void func_ov048_022616b8(UnkStruct_02261120 *p, int val);
extern unsigned int data_ov048_02263d20;

void func_ov048_02261120(UnkStruct_02261120 *p)
{
    char local;
    void *ptr40;
    int ret;

    ptr40 = p->unk_40;
    if (ptr40) {
        func_02068440(ptr40);
    }
    func_02073100();
    if (func_020ec49c() == 0) {
        return;
    }
    if (ptr40) {
        func_ov048_02262378(p);
    }
    ret = func_020984e8();
    if (ret == 0) {
        goto common_exit;
    }
    ret = func_0209985c(ret);
    if (ret < 0 || ret >= 4) {
        goto common_exit;
    }
    func_0209fd54();
    func_0209fcd8();
    func_0209fc60();
    asm {
        mov r0, p
    }
    func_ov048_02262658();
    func_020a01f8();
    if (func_020a1518() == 0) {
        goto common_exit;
    }
    local = 2;
    func_0206844c(p->unk_40, &local, data_ov048_02263d20);
common_exit:
    func_ov048_022616b8(p, 0);
}
