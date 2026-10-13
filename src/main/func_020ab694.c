/* func_020ab694 @ 0x020ab694, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a82e4(void *);
extern void func_020ab8c4(void *);
extern void func_020ab7e8(void);
extern void func_02138c48(void *, int, int, void (*)(void));

void *func_020ab694(void *p)
{
    func_020a82e4((char *) p + 0x354);
    func_020ab8c4((char *) p + 0x2f8);
    func_02138c48(p, 5, 0x90, func_020ab7e8);
    return p;
}
