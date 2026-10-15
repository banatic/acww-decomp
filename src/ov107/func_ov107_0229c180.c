/* func_ov107_0229c180 @ 0x0229c180, 0x88 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_0220afdc(void *);
extern void *func_ov002_0220ba0c(void *);
extern void *func_ov002_02209ac8(void *);
extern void *func_ov002_02209cb4(void *);
extern void func_ov002_02209e38(void *);
extern void *func_ov002_02207e28(void *);
extern void *func_ov094_0229a2d0(void *);
extern void func_ov094_0229bc30(void *);
extern void *func_ov094_0229afe0(void *);
extern void *func_ov002_0220826c(void *);
extern char data_ov107_0229e3b8;

void *func_ov107_0229c180(void *param)
{
    *(void **) param = &data_ov107_0229e3b8;
    func_ov002_0220afdc((char *) param + 0x2828);
    func_ov002_0220ba0c((char *) param + 0x270c);
    func_ov002_02209ac8((char *) param + 0x2318);
    func_ov002_02209cb4((char *) param + 0x22b4);
    func_ov002_02209e38((char *) param + 0x229c);
    func_ov002_02207e28((char *) param + 0x21cc);
    func_ov094_0229a2d0((char *) param + 0x0b94);
    func_ov094_0229bc30((char *) param + 0x0b6c);
    func_ov094_0229afe0((char *) param + 0x010c);
    func_ov002_0220826c(param);
    return param;
}
