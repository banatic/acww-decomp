/* func_ov096_0229dc7c @ 0x0229dc7c, 0x64 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229c2fc(void *, int);
extern int func_ov002_02208ae4(void *);
extern int func_ov002_02208ad8(void *, unsigned char);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_ov002_0220a374(void *, int);

typedef struct {
    unsigned char pad_00[0xbc];
    unsigned char flag;
    unsigned char pad_BD[0x2500 - 0xbd];
    char obj_2500;
    unsigned char pad_2501[0x2564 - 0x2501];
    char obj_2564;
} UnkStruct_0229dc7c;

void func_ov096_0229dc7c(UnkStruct_0229dc7c *arg)
{
    if (func_ov096_0229c2fc(arg, 0x40000)) {
        arg->flag = 1;
    } else {
        arg->flag = 0;
    }
    {
        int v1 = func_ov002_02208ae4(&arg->obj_2564);
        int v2 = func_ov002_02208ad8(&arg->obj_2564, arg->flag);
        func_ov002_0220a0b4(&arg->obj_2500, v1, v2);
    }
    func_ov002_0220a374(&arg->obj_2500, 7);
}
