/* func_0206ebec @ 0x0206ebec, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021cfc28;
extern unsigned short data_021cfc20;
extern int data_021c8c9c;
extern unsigned char data_020e54a8;
extern int data_021cfc24;

extern int func_0206eae4(int);
extern void func_020029e8(int, int);
extern void func_0206efd4(int);
extern void func_0206fcec(void);
extern void func_02001b34(int);
extern void func_02002708(int);
extern void func_020027f0(int);
extern void func_02011f88(void);
extern void func_020ba540(int);
extern void func_0206febc(void);
extern void func_0203de68(int);
extern int FX_MulFunc(int, int);
extern void func_0206fd54(int);

int func_0206ebec(void)
{
    if (data_021cfc28 != 0) {
        goto cleanup;
    }
    if (func_0206eae4(1) != 0) {
        goto cleanup;
    }
    func_020029e8(5, 1);
    func_0206efd4(1);
    func_0206fcec();
    data_021cfc20 = 10;
    data_021c8c9c = 0;
    func_02001b34(14);
    func_02002708(1);
    func_020027f0(5);
    func_02011f88();
    {
        unsigned int cond = (data_020e54a8 == 0) ? 1 : 0;
        if (cond > 0) {
            func_020ba540(0);
        }
    }
    func_0206febc();
    func_0203de68(0);
cleanup:
    if (data_021cfc28 > data_021cfc24) {
        data_021cfc28 = data_021cfc28 - data_021cfc24;
    } else {
        data_021cfc28 = 0;
    }
    func_0206fd54(FX_MulFunc(data_021cfc28, data_021cfc28));
    return 1;
}
