/* func_ov136_0229c518 @ 0x0229c518, 0x3c bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern char *func_ov134_0229beb0(void *);
extern void *func_ov002_0220afdc(void *);
extern void *func_ov002_02209cb4(void *);
extern void *func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);
extern int data_ov136_0229d510;

void *func_ov136_0229c518(void *p)
{
    *(unsigned int *) p = (unsigned int) &data_ov136_0229d510;
    func_ov134_0229beb0((char *) p + 0x2c4);
    func_ov002_0220afdc((char *) p + 0xf8);
    func_ov002_02209cb4((char *) p + 0x94);
    func_ov002_0220826c(p);
    func_ov002_02207f6c(p);
    return p;
}
