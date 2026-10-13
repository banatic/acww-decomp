/* func_020b4070 @ 0x020b4070, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138c48(void *ptr, int n, int m, void (*cb)(void));
extern void func_020b4ab4(void *ptr);
extern void func_020b4c84(void *ptr);
extern void func_020a9b44(void *ptr);
extern void func_020b54b0(void *ptr);
extern void func_020b53f8(void *ptr);
extern void func_020b550c(void);
extern void func_020a8210(void);

void *func_020b4070(void *s)
{
    func_02138c48((char *) s + 0x1964, 0x10, 0x20, func_020b550c);
    func_020b4ab4((char *) s + 0x1934);
    func_020b4c84((char *) s + 0x18f4);
    func_02138c48((char *) s + 0x14fc, 0xb, 0x5c, func_020a8210);
    func_020a9b44((char *) s + 0x0af0);
    func_020b54b0((char *) s + 0x4c);
    func_020b53f8(s);
    return s;
}
