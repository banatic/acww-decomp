/* func_0207689c @ 0x0207689c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020736bc(void *dest, unsigned short *src, unsigned int size);
extern void func_02078794(unsigned int *out1, unsigned int *out2, unsigned short *in1, unsigned short *in2);
extern int func_0207cec0(const void *ptr, unsigned int val);
extern int func_020807c0(int handle, unsigned int val);
extern int func_02081edc(void *object);
extern void func_02081ac0(int handle, void *buf);
extern void *data_020ccf94;

extern unsigned char data_021e5a2c[];

void func_0207689c(int length, int sequence, unsigned char category, unsigned int player)
{
    struct {
        unsigned short a;
        unsigned short b;
        unsigned char pad[4];
        unsigned int c;
        unsigned int d;
    } local;
    int ret1, ret2;

    local.a = 0xfff1;
    func_020736bc(data_020ccf94, &local.b, 3);
    func_02078794(&local.c, &local.d, &local.a, &local.b);

    ret1 = func_0207cec0((void *) data_021e5a2c, local.c);
    if (ret1 != 0) {
        ret2 = func_020807c0(ret1, local.d);
        if (ret2 != 0) {
            if (func_02081edc((void *) ret2)) {
                func_02081ac0(ret2, &local);
            }
        }
    }
}
