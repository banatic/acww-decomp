/* func_ov147_02299c80 @ 0x02299c80, 0x48 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021c75b8;

struct UnkStruct_02299c80 {
    int unk_00;
    int unk_04;
};

extern struct UnkStruct_02299c80 *func_020682e0(int arg);
extern void *func_02068320(struct UnkStruct_02299c80 *arg);
extern int func_020b5e10(void *arg);
extern void func_020b6434(int arg0, int arg1, int arg2, int arg3);
extern void func_020a1924(void);
extern void func_ov147_0229a01c(void *param);

void func_ov147_02299c80(void *param)
{
    unsigned int flag;
    struct UnkStruct_02299c80 *p;

    flag = (data_021c75b8 == 2) ? 1 : 0;
    if (flag != 0) {
        p = func_020682e0(0);
        if (p->unk_04 == 0) {
            func_020b6434(func_020b5e10(func_02068320(p)), 0x2e, 2, 3);
            func_020a1924();
            func_ov147_0229a01c(param);
        }
    }
}
