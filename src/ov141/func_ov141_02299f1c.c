/* func_ov141_02299f1c @ 0x02299f1c, 0x40 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_0220afdc(void *p);
extern void *func_ov002_02209cb4(void *p);
extern void *func_ov139_02299b30(void *p);
extern void *func_ov002_0220826c(void *p);
extern void func_ov002_02207f6c(void *p);

extern unsigned char data_ov141_0229af48[];

void *func_ov141_02299f1c(void *self)
{
    *(void **) self = (void *) data_ov141_0229af48;
    func_ov002_0220afdc((char *) self + 0x0a9c);
    func_ov002_02209cb4((char *) self + 0x0a38);
    func_ov139_02299b30((char *) self + 0x94);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}
