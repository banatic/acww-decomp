/* func_ov099_0229da34 @ 0x0229da34, 0x50 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *p, int n);
extern void func_020027f0(int n);
extern void func_ov002_022080a0(void *p, int n);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);
extern void func_ov099_0229c28c(void *p, int n);

struct UnkStruct_0229da34 {
    char pad_00[0x27ec];
    unsigned int unk_27EC;
};

void func_ov099_0229da34(struct UnkStruct_0229da34 *this)
{
    if (func_ov002_02207f3c(this, 0) != 0) {
        func_020027f0(6);
        func_ov002_022080a0(this, 5);
        func_ov099_0229c28c(this, 1);
        func_ov099_0229c28c(this, 2);
    } else {
        func_ov002_02207e80(this, 6, 0, 0);
    }
    this->unk_27EC = func_ov002_02207f60(this);
}
