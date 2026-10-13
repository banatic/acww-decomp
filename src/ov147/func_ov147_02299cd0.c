/* func_ov147_02299cd0 @ 0x02299cd0, 0x48 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021c75b8;

struct UnkStruct_02299cd0 {
    int a;
    int b;
};

extern struct UnkStruct_02299cd0 *func_020682e0(int);
extern int func_02068320(struct UnkStruct_02299cd0 *);
extern int func_020b5e10(int);
extern int func_020b6434(int, int, int, int);
extern int func_020a1930(int);
extern void func_ov147_0229a01c(int);

void func_ov147_02299cd0(int self)
{
    unsigned int cond = (data_021c75b8 == 2) ? 1 : 0;
    if (cond > 0) {
        struct UnkStruct_02299cd0 *p = func_020682e0(0);
        if (p->b != 0) {
            return;
        }
        func_020a1930(func_020b6434(func_020b5e10(func_02068320(p)), 46, 2, 3));
        func_ov147_0229a01c(self);
    }
}
