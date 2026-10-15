/* func_ov147_0229a0e0 @ 0x0229a0e0, 0x2e bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov147_0229a01c(void *);
extern void func_ov147_0229a6a8(void *receiver);
extern void func_020b9ccc(void *);
extern void func_0203e328(void);
extern void func_020a13e8(void);
int func_ov147_0229a0e0(void *self)
{
    func_ov147_0229a01c(self);
    func_ov147_0229a6a8((char *) self + 0xb0);
    func_020b9ccc((char *) self + 0xd0);
    func_0203e328();
    if (*(int *) ((char *) self + 0x50) == 7) {
        func_020a13e8();
    }
    return 1;
}
