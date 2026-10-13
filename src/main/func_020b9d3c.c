/* func_020b9d3c @ 0x020b9d3c, 0xb6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b9df4(void *, void *, int, void *);
extern int func_02057a50(void *, int);
extern int func_020579f0(void *, int);
extern int func_02057988(void *, int);
extern int func_02057a8c(void *);
extern int func_02057918(void *, int);
extern int func_02057a7c(void *);
extern int func_02057a60(void *);
extern void func_020ba1a8(void *, int, int, int);
extern int func_020ba12c(void *);
extern int func_020ba128(void *);
extern int func_020b9978(void *);
extern int func_020b9e40(void *);
int func_020b9d3c(void *self, void *other, int arg2, void *arg3, int arg4, int arg5)
{
    unsigned char *s = (unsigned char *) self;
    unsigned char *node;
    int val2;
    unsigned char *p;
    int a;
    int b;
    unsigned char *ptr2;
    unsigned char *ptr;
    int c;
    void *ptr3;
    int d;
    int v0;
    int prod;
    unsigned short off;
    unsigned short val;
    ptr3 = arg3;
    func_020b9df4(self, other, arg2, ptr3);
    ptr2 = ((unsigned char *) other) + 8;
    node = ((unsigned char *) other) + (*((unsigned int *) ptr2));
    val2 = (long) arg5;
    v0 = func_02057a50(other, arg2);
    off = *((unsigned short *) (((unsigned char *) node) + 0xa));
    val = *((unsigned short *) ((((unsigned char *) node) + 4) + off));
    prod = val;
    prod = v0 * prod;
    p = ((((unsigned char *) node) + 4) + off) + prod;
    node = ((unsigned char *) node) + (*((unsigned int *) (p + 4)));
    a = func_020579f0(ptr3, arg4);
    b = func_02057988(ptr3, arg5);
    ptr = node;
    c = func_02057a8c(ptr);
    d = func_02057918(arg3, val2);
    off = 3;
    s[0xe] = off;
    func_020ba1a8(s + 0x10, func_02057a7c(ptr), a, c);
    func_020ba1a8(s + 0x1c, func_02057a60(ptr), b, d);
    s[0xf] = (unsigned char) (func_020ba12c(s + 0x10) + func_020ba128(s + 0x1c));
    s[0xc] = 0;
    if (func_020b9978(s) != 0) {
        return 1;
    } else {
        func_020b9e40(s);
        return 0;
    }
}
