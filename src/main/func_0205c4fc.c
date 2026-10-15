/* func_0205c4fc @ 0x0205c4fc, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0205dc3c(void);
extern unsigned char func_020b65c4(void);
extern unsigned int func_020b5df8(unsigned int);
extern unsigned int func_02085f08(void);
extern __arm unsigned int func_020ea0e0(unsigned int, int);
extern unsigned int data_021c9ad4;

unsigned int func_0205c4fc(int param)
{
    unsigned int acc = 0;
    unsigned int total = 0;
    unsigned int a;
    unsigned int sum;

    acc += ((func_0205dc3c() + 3) & ~3u);
    a = func_020b5df8((unsigned int) func_020b65c4());
    sum = a + func_02085f08();
    acc = (acc + 0x4b) & ~3u;
    acc *= sum;

    total += acc;
    return data_021c9ad4 = func_020ea0e0(total, param);
}
