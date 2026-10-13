/* func_ov139_02299b30 @ 0x02299b30, 0x24 bytes, Thumb, module ov139
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070be8(void);
extern void func_02138c48(void *, int, int, void (*)(void));
extern void func_ov002_0220b0f4(void *);

void *func_ov139_02299b30(void *p)
{
    func_02138c48((char *) p + 0xCC, 0x14, 0x6C, func_02070be8);
    func_ov002_0220b0f4(p);
    return p;
}
