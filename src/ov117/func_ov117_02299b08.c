/* func_ov117_02299b08 @ 0x02299b08, 0x38 bytes, Thumb, module ov117
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov117_0229a2f0(void *);
extern void func_ov117_02299c4c(void);
extern void func_ov117_02299c50(void);
extern void func_02138d6c(void *, int, int, void (*)(void), void (*)(void));

void *func_ov117_02299b08(void *self)
{
    func_02138d6c(self, 16, 512, func_ov117_02299c50, func_ov117_02299c4c);
    func_ov117_0229a2f0((char *) self + 8192);
    return self;
}
