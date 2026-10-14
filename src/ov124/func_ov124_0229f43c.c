/* func_ov124_0229f43c @ 0x0229f43c, 0x24 bytes, Thumb, module ov124
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220b3a4(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void));
extern void func_02070be8(void);

void *func_ov124_0229f43c(void *p)
{
    func_ov002_0220b3a4((char *) p + 0x6c);
    __cxa_vec_cleanup(p, 1, 0x6c, func_02070be8);
    return p;
}
