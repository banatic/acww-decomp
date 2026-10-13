/* func_020a6b38 @ 0x020a6b38, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138c48(void *ptr, int a, int b, void (*callback)(void));
extern void func_020a77c8(void);
extern void func_020a76e4(void);
extern void func_020a7718(void);
extern void func_020a7754(void);

void *func_020a6b38(void *self)
{
    func_02138c48((char *) self + 0x3c, 4, 8, func_020a77c8);
    func_02138c48((char *) self + 0x2c, 4, 4, func_020a76e4);
    func_02138c48((char *) self + 0xc, 4, 8, func_020a7718);
    func_02138c48(self, 4, 3, func_020a7754);
    return self;
}
