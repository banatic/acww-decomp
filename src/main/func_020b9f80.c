/* func_020b9f80 @ 0x020b9f80, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9ed8(void *, int, int, int);
extern void func_020ba1a8(void *, int, int, int);
extern unsigned char func_020ba12c(void *);
extern int func_020b9978(void *);
extern void func_020ba004(void *);

int func_020b9f80(void *p0, int p1, int p2, int p3, unsigned char p4)
{
    func_020b9ed8(p0, p1, p2, p3);
    ((unsigned char *) p0)[0xe] = 1;
    func_020ba1a8((char *) p0 + 0x10, p2, p1, p3);
    ((unsigned char *) p0)[0xf] = func_020ba12c((char *) p0 + 0x10);
    ((unsigned char *) p0)[0xc] = p4;
    if (func_020b9978(p0)) {
        return 1;
    }
    func_020ba004(p0);
    return 0;
}
