/* func_ov104_0229e54c @ 0x0229e54c, 0xbc bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208e28(unsigned char *);
extern int func_ov002_02208054(unsigned char *, int);
extern void func_ov104_0229cfe4(unsigned char *);
extern int func_ov002_02208b00(unsigned char *, unsigned char, unsigned char);
extern int func_ov104_0229c364(unsigned char *, int);
extern void func_ov002_02209114(unsigned char *, int, int);
extern void func_ov002_02208098(unsigned char *, int);
extern void RtcSendPxiCommand(unsigned int);

extern unsigned char data_021f6c54;
extern unsigned char data_021f6c58;
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;

void func_ov104_0229e54c(unsigned char *p)
{
    int r;
    int do_x;
    unsigned int flag;
    unsigned char *q;

    if (func_ov002_02208e28(p + 0x2504) == 0) {
        return;
    }
    if (func_ov002_02208054(p, 1) != 0) {
        func_ov104_0229cfe4(p);
        return;
    }
    flag = (data_021fbdd8 != 0) && (data_021fbddc != 0);
    if (flag == 0) {
        return;
    }
    r = func_ov002_02208b00(p + 0x2504, data_021f6c58, data_021f6c54);
    if (r < 0) {
        return;
    }
    if (func_ov104_0229c364(p, 0x8000) != 0 && r == 0) {
        return;
    }
    q = p + r;
    p[0xbc] = q[0x28f1];
    do_x = 1;
    if (p[0xbc] == 2) {
        do_x = 0;
        RtcSendPxiCommand(0x24);
    }
    func_ov002_02209114(p + 0x2504, r, do_x);
    func_ov002_02208098(p, 0x17);
}
