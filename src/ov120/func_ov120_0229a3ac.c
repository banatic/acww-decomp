/* func_ov120_0229a3ac @ 0x0229a3ac, 0x74 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138c48(void *ptr, int a, int b, void (*cb)(void));
extern void func_ov002_02209cb4(void *ptr);
extern void func_ov002_0220a5e4(void *ptr);
extern void func_ov002_0220826c(void *ptr);
extern void func_ov002_02207f6c(void *ptr);
extern void func_ov120_0229a420(void);
extern void func_02070be8(void);
extern char data_ov120_0229c650[];

void *func_ov120_0229a3ac(void *self)
{
    int count = 3;

    *(void **) self = data_ov120_0229c650;
    func_02138c48((char *) self + 0x2743, 14, count, func_ov120_0229a420);
    func_02138c48((char *) self + 0x273a, count, count, func_ov120_0229a420);
    func_ov002_02209cb4((char *) self + 0x6bc);
    func_ov002_0220a5e4((char *) self + 0x674);
    func_02138c48((char *) self + 0xf8, 13, 0x6c, func_02070be8);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}
