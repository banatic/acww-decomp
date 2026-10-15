/* func_0208893c @ 0x0208893c, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e1f68[];
extern unsigned char data_020e1fdc[];
extern unsigned char data_020e1f60[];
extern void func_02066694(void *);
extern int func_020984e8(void);
extern int func_02099870(int);
extern void func_02066024(void *, unsigned char *, void *, void *, void *, int);
extern unsigned short func_02065ed0(void *, unsigned int, int);
extern int func_020979f0(void *, int);
extern void func_02066688(void *);

int func_0208893c(int a0, int a1, unsigned short *a2)
{
    unsigned int ok;
    int t;
    int r;
    unsigned char c;
    int buf[0x40];
    func_02066694(buf);
    c = 0;
    t = func_020984e8();
    c = (unsigned char) a1;
    r = func_02099870(t);
    func_02066024(buf, &c, data_020e1fdc, data_020e1f60, data_020e1f68, r);
    func_02065ed0(buf, *a2, 1);
    if (func_020979f0(buf, 0) != 0) {
        ok = 1;
    } else {
        ok = 0;
    }
    func_02066688(buf);
    return ok;
}
