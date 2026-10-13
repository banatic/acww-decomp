/* func_0205f9d4 @ 0x0205f9d4, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020778b0(void *buf, int param3);
extern void func_02077a54(void *p, int a, unsigned char b);
extern int func_020a7278(void);
extern void func_0205fa40(void *buf);
extern void *data_020ccf94;
extern void func_02073820(void *base);
extern void func_020737f0(void *base, void *flags, int mode);
extern void func_02073770(void *base, int id, int val);

void func_0205f9d4(unsigned char p0, unsigned char p1, int p2, int p3, int p4)
{
    unsigned char buf[8];
    int flag;

    func_020778b0(buf, p3);

    flag = (p4 != 0) ? 1 : 0;

    func_02077a54(buf + 2, p2, flag);

    buf[3] = p0;
    buf[4] = p1;

    if (func_020a7278()) {
        func_0205fa40(buf);
    } else {
        void *base = data_020ccf94;
        func_02073820(base);
        func_020737f0(base, buf, 5);
        func_02073770(base, 0x13, 6);
    }
}
