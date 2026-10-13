/* func_ov129_0229b774 @ 0x0229b774, 0x58 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov129_0229dc38;
extern void func_ov127_0229a0e8(void *);
extern void func_020b18a8(void *);
extern void func_ov002_02209cb4(void *);
extern void func_ov002_0220afdc(void *);
extern void func_ov002_0220ba0c(void *);
extern void func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);

void *func_ov129_0229b774(void *p)
{
    *(void **) p = (void *) &data_ov129_0229dc38;
    func_ov127_0229a0e8((char *) p + 0x734);
    func_020b18a8((char *) p + 0x404);
    func_ov002_02209cb4((char *) p + 0x3a0);
    func_ov002_0220afdc((char *) p + 0x1d4);
    func_ov002_0220ba0c((char *) p + 0xb8);
    func_ov002_0220826c(p);
    func_ov002_02207f6c(p);
    return p;
}
