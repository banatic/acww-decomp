/* func_ov125_0229f6a0 @ 0x0229f6a0, 0x54 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov125_022a0ab8;
extern void *func_ov002_0220afdc(void *);
extern void *func_ov002_02209cb4(void *);
extern void *func_ov002_02207e28(void *);
extern void *func_ov002_02209ac8(void *);
extern void *func_ov124_0229f43c(void *);
extern void *func_ov002_0220826c(void *);

void *func_ov125_0229f6a0(void *p)
{
    ((int *) p)[0] = (int) &data_ov125_022a0ab8;
    func_ov002_0220afdc((char *) p + 0x6a8);
    func_ov002_02209cb4((char *) p + 0x644);
    func_ov002_02207e28((char *) p + 0x574);
    func_ov002_02209ac8((char *) p + 0x180);
    func_ov124_0229f43c((char *) p + 0x94);
    func_ov002_0220826c(p);
    return p;
}
