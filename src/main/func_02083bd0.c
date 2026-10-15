/* func_02083bd0 @ 0x02083bd0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083cb8(int p);
extern void func_0205cce4(void *);
extern void func_0205cce8(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));

int func_02083bd0(int p)
{
    func_02083cb8(p);
    __cxa_vec_ctor((void *) (p + 1), 3, 1, (void (*)(void *)) func_0205cce8, (void (*)(void *)) func_0205cce4);
    return p;
}
