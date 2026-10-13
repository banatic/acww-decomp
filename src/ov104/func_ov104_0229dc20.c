/* func_ov104_0229dc20 @ 0x0229dc20, 0x48 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov104_0229d4a8(void *p, int v);
extern void func_ov104_0229d554(void *p);
extern void func_ov094_022999c0(void);
extern void func_ov002_02207d24(void *p, int v);
extern void func_ov002_02208098(void *p, int v);

void func_ov104_0229dc20(void *p, int v)
{
    char *q = (char *) p + 0xb7;
    *q = (char) v;
    func_ov002_02207d24((char *) p + 0x23b8, 1);
    func_ov104_0229d4a8(p, v);
    if (((unsigned char *) p)[0xb4] == 1) {
        func_ov002_02208098(p, 4);
    }
    func_ov104_0229d554(p);
    func_ov094_022999c0();
}
