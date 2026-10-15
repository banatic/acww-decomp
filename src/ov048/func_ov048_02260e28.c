/* func_ov048_02260e28 @ 0x02260e28, 0x50 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206844c(void *a, char *b, int c);
extern unsigned char func_020ec1e8(void);
extern void func_ov048_02262378(void *a);
extern int func_ov048_02262658(void);
extern void func_ov048_022616b8(void *a, int b);
extern int data_ov048_02263d20;

typedef struct {
    char pad_00[0x40];
    void *ptr;
} UnkStruct_02260e28;

void func_ov048_02260e28(UnkStruct_02260e28 *param1, char param2)
{
    char local;
    int v;
    local = param2;
    func_0206844c(param1->ptr, &local, data_ov048_02263d20);
    v = func_020ec1e8();
    if (v == 3 || func_020ec1e8() == 4) {
        func_ov048_022616b8(param1, 0x14);
    } else {
        func_ov048_02262378(param1);
        asm {
            mov r0, param1
        }
        func_ov048_02262658();
        func_ov048_022616b8(param1, 0);
    }
}
