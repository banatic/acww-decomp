/* func_ov109_0229c180 @ 0x0229c180, 0x84 bytes, Thumb, module ov109
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

extern unsigned char data_ov109_0229dbd8[];

void *func_ov109_0229c180(void *obj)
{
    *(void **) obj = (void *) data_ov109_0229dbd8;
    func_ov002_0220afdc((char *) obj + 0x27e8);
    func_ov002_0220ba0c((char *) obj + 0x26cc);
    func_ov002_02209ac8((char *) obj + 0x22d8);
    func_ov002_02209cb4((char *) obj + 0x2274);
    func_ov002_02209e38((char *) obj + 0x225c);
    func_ov002_02207e28((char *) obj + 0x218c);
    func_ov094_0229a2d0((char *) obj + 0x0b54);
    func_ov094_0229bc30((char *) obj + 0x0b2c);
    func_ov094_0229afe0((char *) obj + 0x0cc);
    func_ov002_0220826c(obj);
    return obj;
}
