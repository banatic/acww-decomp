/* func_02083bd0 @ 0x02083bd0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083cb8(int p);
extern void func_0205cce4(void);
extern void func_0205cce8(void);
extern void __cxa_vec_ctor(int p, int a, int b, void (*f1)(void), void (*f2)(void));

int func_02083bd0(int p)
{
    func_02083cb8(p);
    __cxa_vec_ctor(p + 1, 3, 1, func_0205cce8, func_0205cce4);
    return p;
}
