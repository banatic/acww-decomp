/* func_020a6998 @ 0x020a6998, 0xda bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a772c(char *);
extern void func_020a76f8(char *);
extern void func_020a76d0(char *);
extern void func_020a7768(char *);
extern void func_020a5c00(char *);
extern void func_020a5be8(char *);
extern void func_020a5bd0(char *);
extern void func_020a5b98(char *);
extern void func_020a5748(char *, int);
extern void func_020a6160(char *);
extern void func_020a6368(char *, int);
extern void func_020a6340(char *);
extern void func_020a633c(char *, int);
extern void func_020a6688(char *, int);
extern void func_020a6288(char *, int);
extern void func_020a6280(char *, int);
extern void func_020a6290(char *, int);
extern void func_020a6248(char *, int);
extern void func_020a6238(char *, int);
extern void func_020a5c30(char *, int);
extern void func_020a6694(char *, int);
extern void func_020a5738(char *, int);
extern void func_020a5728(char *, int);
extern void func_020a5718(char *, int);

void func_020a6998(char *self)
{
    int n = 3;
    int i;
    for (i = n; i >= 0; i--) {
        func_020a772c(self + i * n);
        func_020a76f8(self + 0xc + i * 8);
        func_020a76d0(self + 0x2c + i * 4);
        func_020a7768(self + 0x3c + i * 8);
    }
    func_020a5c00(self);
    func_020a5be8(self);
    func_020a5bd0(self);
    func_020a5b98(self);
    func_020a5748(self, 0);
    func_020a6160(self);
    func_020a6368(self, 4);
    func_020a6340(self);
    func_020a633c(self, 4);
    func_020a6688(self, 16);
    func_020a6288(self, 4);
    func_020a6280(self, 4);
    func_020a6290(self, 4);
    func_020a6248(self, 0);
    func_020a6238(self, 4);
    func_020a5c30(self, 4);
    func_020a6694(self, 0);
    func_020a5738(self, 0);
    func_020a5728(self, 4);
    func_020a5718(self, 0);
}
