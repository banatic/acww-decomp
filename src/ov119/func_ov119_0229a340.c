/* func_ov119_0229a340 @ 0x0229a340, 0x5c bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov119_0229cea0;
extern void func_ov002_0220ba0c(void *);
extern void func_ov002_02209cb4(void *);
extern void func_020780b8(void *);
extern void func_02138c48(void *, int, int, void (*)(void));
extern void func_02070be8(void);
extern void func_ov002_02209ac8(void *);
extern void func_ov002_0220826c(void *);

void *func_ov119_0229a340(void *arg)
{
    void *p = arg;
    *(void **) p = (void *) &data_ov119_0229cea0;
    func_ov002_0220ba0c((char *) p + 0x1efc);
    func_ov002_02209cb4((char *) p + 0xda8);
    func_020780b8((char *) p + 0xcd4);
    func_02138c48((char *) p + 0x4d0, 0x13, 0x6c, &func_02070be8);
    func_ov002_02209ac8((char *) p + 0xdc);
    func_ov002_0220826c(p);
    return p;
}
