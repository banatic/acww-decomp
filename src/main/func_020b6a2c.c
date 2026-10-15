/* func_020b6a2c @ 0x020b6a2c, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b698c(void *object);
extern void NNS_G3dGeFlushBuffer(void);
extern int func_020b6590(void);
extern void func_020b75b8(int, unsigned char, unsigned char, int);
extern void func_020348f8(void);
extern void func_02089ce0(void);
extern unsigned char data_021fbdd8;
extern unsigned short data_021fbde0;
extern unsigned short data_021fbde4;

int func_020b6a2c(void *object)
{
    int first_arg;
    int flag;
    unsigned char u1;
    unsigned char u2;

    first_arg = 0;
    flag = 0;
    u1 = 0;
    u2 = 0;

    func_020b698c(object);
    NNS_G3dGeFlushBuffer();
    first_arg = func_020b6590();
    flag = (data_021fbdd8 != 0);
    u1 = (unsigned char) data_021fbde0;
    u2 = (unsigned char) data_021fbde4;
    func_020b75b8(first_arg, u1, u2, flag);
    func_020348f8();
    func_02089ce0();
    return 1;
}
