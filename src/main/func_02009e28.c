/* func_02009e28 @ 0x02009e28, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109a0(void *, int, int, unsigned short);
extern void *func_02057cf4(void);
extern void *func_02057d0c(void *, void *);
extern int func_0200f328(void *, int);

void func_02009e28(void *param, void *message, int previous)
{
    func_02057d0c((func_020109a0(param, 0x2c, 3, 0), func_02057cf4()), param);
    func_0200f328(param, 0x4f);
}
