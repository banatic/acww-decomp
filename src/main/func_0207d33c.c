/* func_0207d33c @ 0x0207d33c, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020951bc(int);
extern int func_02003704(int);
extern void func_02066694(void *);
extern int func_020036e8(int);
extern unsigned char func_0209765c(int);
extern int func_0200366c(int, void *, int, int);
extern void func_020662bc(void *, unsigned char *, void *, unsigned char *, int, int, int);
extern unsigned short func_02065ed0(void *, unsigned short, int);
extern int func_020979f0(void *, int);
extern void func_02066688(void *);
extern int data_021d1380;

int func_0207d33c(int a, int b, int c, int d, void *e)
{
    unsigned char bytearr[2];
    unsigned int buf[65];

    if (func_020951bc(c) == 0) {
        goto fail;
    }
    if (func_02003704(d) == 0) {
        goto fail;
    }
    func_02066694(buf);
    bytearr[0] = func_0209765c(func_020036e8(d));
    func_0200366c(d, &data_021d1380, 0x28, a);
    bytearr[1] = b;
    func_020662bc(buf, bytearr + 1, &data_021d1380, bytearr, d, c, 1);
    if (e && *(unsigned short *) e != 0xfff1) {
        func_02065ed0(buf, *(unsigned short *) e, 1);
    }
    if (func_020979f0(buf, 0) != 0) {
        func_02066688(buf);
        return 1;
    }
    func_02066688(buf);
fail:
    return 0;
}
