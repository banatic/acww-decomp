/* func_ov110_0229c180 @ 0x0229c180, 0x90 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov110_0229ecb8;
extern void __cxa_vec_cleanup(char *ptr, int a, int b, void (*cb)(void));
extern void func_ov002_0220ba0c(char *ptr);
extern void func_ov002_02209ac8(char *ptr);
extern void func_ov002_02209cb4(char *ptr);
extern void func_ov002_02209e38(char *ptr);
extern void func_ov002_02207e28(char *ptr);
extern void func_ov094_0229a2d0(char *ptr);
extern void func_ov094_0229bc30(char *ptr);
extern void func_ov094_0229afe0(char *ptr);
extern void func_ov002_0220826c(char *ptr);
extern void func_02070be8(void);

char *func_ov110_0229c180(char *p)
{
    *(unsigned int *) p = (unsigned int) &data_ov110_0229ecb8;
    __cxa_vec_cleanup(p + 0x2854, 2, 0x6c, func_02070be8);
    func_ov002_0220ba0c(p + 0x2738);
    func_ov002_02209ac8(p + 0x2344);
    func_ov002_02209cb4(p + 0x22e0);
    func_ov002_02209e38(p + 0x22c8);
    func_ov002_02207e28(p + 0x21f8);
    func_ov094_0229a2d0(p + 0xbc0);
    func_ov094_0229bc30(p + 0xb98);
    func_ov094_0229afe0(p + 0x138);
    func_ov002_0220826c(p);
    return p;
}
