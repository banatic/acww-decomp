/* func_ov122_0229eea0 @ 0x0229eea0, 0x90 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220ba0c(void *p);
extern void func_ov002_0220afdc(void *p);
extern void func_ov002_02209ac8(void *p);
extern void func_02065c98(void *p);
extern void func_0206da80(void *p);
extern void func_ov002_02209cb4(void *p);
extern void func_ov002_0220a5e4(void *p);
extern void func_0206e35c(void *p);
extern void func_02138c48(void *p, int a, int b, void *fp);
extern void func_ov002_0220826c(void *p);
extern void func_02070be8(void);
extern char data_ov122_022a2738;

void *func_ov122_0229eea0(void *param)
{
    *(void **) param = &data_ov122_022a2738;
    func_ov002_0220ba0c((void *) ((char *) param + 0x4864));
    func_ov002_0220afdc((void *) ((char *) param + 0x4698));
    func_ov002_02209ac8((void *) ((char *) param + 0x42b0));
    func_02065c98((void *) ((char *) param + 0x4150));
    func_0206da80((void *) ((char *) param + 0x40bc));
    func_ov002_02209cb4((void *) ((char *) param + 0x4058));
    func_ov002_0220a5e4((void *) ((char *) param + 0x4010));
    func_0206e35c((void *) ((char *) param + 0x3ce8));
    func_02138c48((void *) ((char *) param + 0x2410), 2, 0x6c, (void *) &func_02070be8);
    func_ov002_0220826c(param);
    return param;
}
