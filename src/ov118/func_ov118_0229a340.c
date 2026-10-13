/* func_ov118_0229a340 @ 0x0229a340, 0x78 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov118_0229cc08;
extern void func_02138c48(void *a, int b, int c, void *d);
extern void func_ov117_0229a2ec(void *a);
extern void func_ov002_02209cb4(void *a);
extern void func_ov002_0220a5e4(void *a);
extern void func_ov002_0220826c(void *a);
extern void func_ov118_0229a438(void);
extern void func_02070be8(void);

void *func_ov118_0229a340(void *self)
{
    *(int *) self = (int) &data_ov118_0229cc08;
    func_02138c48((char *) self + 0x47ad, 14, 3, (void *) func_ov118_0229a438);
    func_02138c48((char *) self + 0x47a4, 3, 3, (void *) func_ov118_0229a438);
    func_ov117_0229a2ec((char *) self + 0x4724);
    func_ov002_02209cb4((char *) self + 0x6c0);
    func_ov002_0220a5e4((char *) self + 0x678);
    func_02138c48((char *) self + 0xfc, 13, 0x6c, (void *) func_02070be8);
    func_ov002_0220826c(self);
    return self;
}
