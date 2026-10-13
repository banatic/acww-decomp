/* func_ov102_0229e32c @ 0x0229e32c, 0x54 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov102_0229cb50(void *);
extern void func_ov002_02207d24(void *, int);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern void func_ov002_02207e90(void *, int);
extern void func_ov002_02207e80(void *, int, int, int);
extern int func_ov002_02207f60(void *);

void func_ov102_0229e32c(void *r0)
{
    func_ov002_02207d24((char *) r0 + 0x218c, 1);
    func_ov102_0229cb50(r0);
    func_ov002_02207f04(r0, 2, 4, 1, 0x30);
    func_ov002_02207e90(r0, 0x90);
    func_ov002_02207e80(r0, 4, 0, 0);
    *(int *) ((char *) r0 + 0x24d4) = func_ov002_02207f60(r0);
}
