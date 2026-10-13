/* func_020c2098 @ 0x020c2098, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void *p);
extern void func_0208602c(void);
extern void func_020860c4(void);
extern void func_02087f20(void);
extern unsigned short data_020c80f8;
extern int func_02019c20(void *ptr, int a, int b, int c, unsigned short e, int f);
extern int func_020c1b28(void *ptr, int a);
extern int func_020044c0(void *ptr, int a, int b, int c);

int func_020c2098(void *p)
{
    if (func_020b65c4(p) == 0) {
        func_0208602c();
        func_020860c4();
        func_02087f20();
    }
    func_02019c20((char *) p + 0x564, 1, 0x122, 1, data_020c80f8, 0);
    func_020c1b28((char *) p + 0x658, 4);
    func_020044c0((char *) p + 0x514, 0x7db, 0x7f, 0);
    return 1;
}
