/* func_ov109_0229c204 @ 0x0229c204, 0x88 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov109_0229dbd8;
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
extern void func_ov002_02207f6c(void *);

void *func_ov109_0229c204(void *obj)
{
    char *base = (char *) obj;
    *((void **) base) = (void *) &data_ov109_0229dbd8;
    func_ov002_0220afdc((void *) (base + 0x27e8));
    func_ov002_0220ba0c((void *) (base + 0x26cc));
    func_ov002_02209ac8((void *) (base + 0x22d8));
    func_ov002_02209cb4((void *) (base + 0x2274));
    func_ov002_02209e38((void *) (base + 0x225c));
    func_ov002_02207e28((void *) (base + 0x218c));
    func_ov094_0229a2d0((void *) (base + 0x0b54));
    func_ov094_0229bc30((void *) (base + 0x0b2c));
    func_ov094_0229afe0((void *) (base + 0xcc));
    func_ov002_0220826c((void *) base);
    func_ov002_02207f6c((void *) base);
    return obj;
}
