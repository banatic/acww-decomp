/* func_ov134_0229beb0 @ 0x0229beb0, 0x24 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138c48(void *, int, int, void (*)(void));
extern void func_ov002_0220a5e4(void *);
extern void func_02070be8(void);

char *func_ov134_0229beb0(char *obj)
{
    func_02138c48(obj + 0xd8, 0x11, 0x6c, func_02070be8);
    func_ov002_0220a5e4(obj + 0x18);
    return obj;
}
