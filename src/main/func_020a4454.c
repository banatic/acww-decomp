/* func_020a4454 @ 0x020a4454, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021c75b8;
extern unsigned int data_021dc7a8;
typedef struct {
    unsigned int pad_00;
    unsigned int unk_04;
} ResultStruct;
extern ResultStruct *func_020682e0(int);
extern void func_02068320(void);
extern int func_0209f150(void *ptr, unsigned int value);
extern void func_020a1308(void);
extern void func_020a12fc(void);
extern void func_020a13e8(void);
extern int func_020b5e10(void);
extern void func_020b6434(int a, unsigned int b, unsigned int c, unsigned int d);
extern void func_020a4e94(void *param, unsigned int value);
volatile unsigned char func_020a4454(void *arg0)
{
    ResultStruct *result;
    unsigned int flag;
    result = func_020682e0(0);
    flag = data_021c75b8 == 2;
    if (flag == 0) {
        return;
    }
    if (result->unk_04 != 0) {
        return;
    }
    func_02068320();
    if (func_0209f150(&data_021dc7a8, 0x12) != 0) {
        func_020a1308();
    } else {
        func_020a12fc();
    }
    func_020a13e8();
    func_020b6434(func_020b5e10(), 0x2d, 3, 0);
    func_020a4e94(arg0, 0);
}
