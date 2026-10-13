/* func_ov090_0229915c @ 0x0229915c, 0x40 bytes, Thumb, module ov090
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(int);
extern void func_02036470(void *, int);

extern unsigned char data_021c526c[];

void func_ov090_0229915c(void *arg0)
{
    char *p;
    int *g;
    int *addr;

    p = (char *) arg0;
    p[0x91] = 0;
    p[0x92] = 0;
    p[0x94] = 0;
    p[0x95] = 0;

    RtcSendPxiCommand(1);

    g = (int *) data_021c526c;
    addr = (int *) (*g + 0x1c4);
    func_02036470(addr, 0);
}
