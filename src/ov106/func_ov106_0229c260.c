/* func_ov106_0229c260 @ 0x0229c260, 0xe4 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov106_0229f6e0;
extern void func_02066688(void *);
extern void *func_0206e35c(void *);
extern void *func_ov002_0220afdc(void *);
extern void *func_ov002_0220b464(void *);
extern void *func_ov002_0220ba0c(void *);
extern void *func_ov002_02209ac8(void *);
extern void *func_ov002_02209cb4(void *);
extern void func_ov002_02209e38(void *);
extern void *func_ov002_02207e28(void *);
extern void *func_ov094_0229a2d0(void *);
extern void func_ov094_0229bc30(void *);
extern void *func_ov094_0229afe0(void *);
extern void *func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));

void *func_ov106_0229c260(void *self)
{
    char *p = (char *) self;
    *(unsigned int *) p = (unsigned int) &data_ov106_0229f6e0;
    func_02066688(p + 0x4280);
    func_02066688(p + 0x4180);
    func_ov002_0220afdc(p + 0x3fb4);
    __cxa_vec_cleanup(p + 0x35b4, 10, 0x100, func_02066688);
    __cxa_vec_cleanup(p + 0x2bb4, 10, 0x100, func_02066688);
    func_ov002_0220b464(p + 0x2b3c);
    func_0206e35c(p + 0x2814);
    func_ov002_0220ba0c(p + 0x26f8);
    func_ov002_02209ac8(p + 0x2304);
    func_ov002_02209cb4(p + 0x22a0);
    func_ov002_02209e38(p + 0x2288);
    func_ov002_02207e28(p + 0x21b8);
    func_ov094_0229a2d0(p + 0x0b80);
    func_ov094_0229bc30(p + 0x0b58);
    func_ov094_0229afe0(p + 0xf8);
    func_ov002_0220826c(p);
    func_ov002_02207f6c(p);
    return self;
}
