/* func_ov099_0229c204 @ 0x0229c204, 0x88 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov099_0229e040;
extern void func_02066688(void *);
extern void func_ov002_0220ba0c(void *);
extern void func_ov002_02209ac8(void *);
extern void func_ov002_02209cb4(void *);
extern void func_ov002_02209e38(void *);
extern void func_ov002_02207e28(void *);
extern void func_ov094_0229a2d0(void *);
extern void func_ov094_0229bc30(void *);
extern void func_ov094_0229afe0(void *);
extern void func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);

void *func_ov099_0229c204(void *obj)
{
    *(int *) obj = (int) &data_ov099_0229e040;
    func_02066688((char *) obj + 0x2800);
    func_ov002_0220ba0c((char *) obj + 0x26cc);
    func_ov002_02209ac8((char *) obj + 0x22d8);
    func_ov002_02209cb4((char *) obj + 0x2274);
    func_ov002_02209e38((char *) obj + 0x225c);
    func_ov002_02207e28((char *) obj + 0x218c);
    func_ov094_0229a2d0((char *) obj + 0x0b54);
    func_ov094_0229bc30((char *) obj + 0x0b2c);
    func_ov094_0229afe0((char *) obj + 0xcc);
    func_ov002_0220826c(obj);
    func_ov002_02207f6c(obj);
    return obj;
}
