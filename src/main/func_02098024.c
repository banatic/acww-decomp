/* func_02098024 @ 0x02098024, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int __arm __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void func_02066688(void *);
extern void func_02066694(void *);

int func_02098024(int x)
{
    __cxa_vec_ctor((void *) (x), 10, 0x100, (void (*)(void *)) func_02066694, (void (*)(void *)) func_02066688);
    return x;
}
