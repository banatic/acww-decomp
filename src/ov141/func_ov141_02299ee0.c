/* func_ov141_02299ee0 @ 0x02299ee0, 0x3c bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov141_0229af48;

extern void func_ov002_0220afdc(void *p);
extern void func_ov002_02209cb4(void *p);
extern void func_ov139_02299b30(void *p);
extern void func_ov002_0220826c(void *p);

void *func_ov141_02299ee0(void *p)
{
    *(void **) p = (void *) &data_ov141_0229af48;
    func_ov002_0220afdc((char *) p + 0xA9C);
    func_ov002_02209cb4((char *) p + 0xA38);
    func_ov139_02299b30((char *) p + 0x94);
    func_ov002_0220826c(p);
    return p;
}
