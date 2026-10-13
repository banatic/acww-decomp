/* func_ov108_0229c21c @ 0x0229c21c, 0xa0 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov108_0229e098[];

extern void func_ov002_0220afdc(void *p);
extern void func_ov002_0220ba0c(void *p);
extern void func_ov002_02209ac8(void *p);
extern void func_ov002_02209cb4(void *p);
extern void func_ov002_02209e38(void *p);
extern void func_ov002_02207e28(void *p);
extern void func_ov094_0229a2d0(void *p);
extern void func_ov094_0229bc30(void *p);
extern void func_ov094_0229afe0(void *p);
extern void func_02066688(void *p);
extern void func_ov002_0220826c(void *p);
extern void func_ov002_02207f6c(void *p);

void *func_ov108_0229c21c(void *obj)
{
    *(void **) obj = data_ov108_0229e098;
    func_ov002_0220afdc((char *) obj + 0x2a0c);
    func_ov002_0220ba0c((char *) obj + 0x28f0);
    func_ov002_02209ac8((char *) obj + 0x24fc);
    func_ov002_02209cb4((char *) obj + 0x2498);
    func_ov002_02209e38((char *) obj + 0x2480);
    func_ov002_02207e28((char *) obj + 0x23b0);
    func_ov094_0229a2d0((char *) obj + 0x0d78);
    func_ov094_0229bc30((char *) obj + 0x0d50);
    func_ov094_0229afe0((char *) obj + 0x02f0);
    func_02066688((char *) obj + 0x01ac);
    func_02066688((char *) obj + 0xac);
    func_ov002_0220826c(obj);
    func_ov002_02207f6c(obj);
    return obj;
}
