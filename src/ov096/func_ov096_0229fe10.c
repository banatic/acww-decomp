/* func_ov096_0229fe10 @ 0x0229fe10, 0x64 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229a3b0(const void *);
extern int func_020984e8(void);
extern void func_02098ff8(int, int);
extern void func_ov096_0229e898(void *, unsigned char, int);
extern void func_ov096_0229fb9c(void *);

void func_ov096_0229fe10(void *ptr)
{
    if (func_ov094_0229a3b0((char *) ptr + 0x358) != 0) {
        int ret = func_020984e8();
        unsigned short val = *(unsigned short *) ((char *) ptr + 0xac);
        if (val == 0x136a) {
            func_02098ff8(ret, 0x27);
        } else if (val == 0x137b) {
            func_02098ff8(ret, 0x28);
        }
        *(unsigned char *) ((char *) ptr + 0xb0) = 0;
        func_ov096_0229e898(ptr, *(unsigned char *) ((char *) ptr + 0xb6), 1);
        func_ov096_0229fb9c(ptr);
    }
}
