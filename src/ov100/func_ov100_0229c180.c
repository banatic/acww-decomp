/* func_ov100_0229c180 @ 0x0229c180, 0x8c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov100_0229ecb8[];
extern void func_02070be8(void);
extern void func_02138c48(void *, int, int, void (*)(void));
extern void func_ov002_0220ba0c(void *);
extern void func_ov002_02209ac8(void *);
extern void func_ov002_02209cb4(void *);
extern void func_ov002_02209e38(void *);
extern void func_ov002_02207e28(void *);
extern void func_ov094_0229a2d0(void *);
extern void func_ov094_0229bc30(void *);
extern void func_ov094_0229afe0(void *);
extern void func_ov002_0220826c(void *);

void *func_ov100_0229c180(void *obj)
{
    char *base = (char *) obj;
    *(void **) obj = data_ov100_0229ecb8;
    func_02138c48(base + 0x27e8, 2, 0x6c, func_02070be8);
    func_ov002_0220ba0c(base + 0x26cc);
    func_ov002_02209ac8(base + 0x22d8);
    func_ov002_02209cb4(base + 0x2274);
    func_ov002_02209e38(base + 0x225c);
    func_ov002_02207e28(base + 0x218c);
    func_ov094_0229a2d0(base + 0x0b54);
    func_ov094_0229bc30(base + 0x0b2c);
    func_ov094_0229afe0(base + 0xcc);
    func_ov002_0220826c(obj);
    return obj;
}
