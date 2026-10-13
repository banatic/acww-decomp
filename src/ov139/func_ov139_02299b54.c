/* func_ov139_02299b54 @ 0x02299b54, 0x3c bytes, Thumb, module ov139
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220b10c(void *p);
extern void func_02138d6c(void *data, int a, int b, void (*cb1)(void), void (*cb2)(void));
extern void func_020b9cfc(void *p);
extern void func_02070be8(void);
extern void func_02070c08(void);

void *func_ov139_02299b54(void *p)
{
    func_ov002_0220b10c(p);
    func_02138d6c((char *) p + 0xcc, 0x14, 0x6c, func_02070c08, func_02070be8);
    func_020b9cfc((char *) p + 0x93c);
    return p;
}
