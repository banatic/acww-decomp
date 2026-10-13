/* func_0205f524 @ 0x0205f524, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138c48(void *, int, int, void (*)(void));
extern void func_020051b0(void);
extern void func_02054e18(void);
extern void func_02055ce8(void);

void *func_0205f524(void *p)
{
    func_02138c48((char *) p + 0xb44, 9, 2, func_020051b0);
    func_02138c48((char *) p + 0x28c, 9, 0xf4, func_02054e18);
    func_02138c48((char *) p + 0xdc, 9, 0x14, func_02055ce8);
    return p;
}
