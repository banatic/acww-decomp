/* func_020a75d4 @ 0x020a75d4, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02073410(void *);
extern unsigned long func_02073424(void *);
extern unsigned char func_020b65c4(void);
extern void MI_CpuCopy8(void *, int, int);
extern void func_02073404(void *, int);
extern int *data_020ccf94;
extern void (*data_020d1c3c[2])(int);

struct Msg {
    unsigned short a;
    unsigned short b;
    unsigned char c;
};

void func_020a75d4(void)
{
    int d;
    int r7;
    int r6;
    unsigned int r5;
    int *p;
    int s0;
    int s4;
    int s8;
    struct Msg msg;

    p = data_020ccf94;
    func_02073410(p);
    r7 = func_02073424(p);
    r6 = r7 + 2;
    s0 = func_020b65c4();
    for (r5 = 0; r5 < 2; r5++) {
        p[0x41] = r6 + 4;
        s4 = p[0x41];
        data_020d1c3c[r5](s0);
        s8 = p[0x41];
        d = s8 - s4;
        if (d != 0) {
            msg.b = (unsigned short) d;
            msg.c = (unsigned char) r5;
            MI_CpuCopy8(&msg.b, r6, 4);
            r6 = s8;
        }
    }
    r5 = r6 - r7;
    msg.a = (unsigned short) (r5 - 2);
    MI_CpuCopy8(&msg, r7, 2);
    func_02073404(p, r5);
}
