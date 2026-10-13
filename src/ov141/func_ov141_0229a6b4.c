/* func_ov141_0229a6b4 @ 0x0229a6b4, 0x30 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f64(void *);
extern void func_ov002_02208098(void *, unsigned char);
extern void func_ov141_0229abc0(void *);

void func_ov141_0229a6b4(void *a)
{
    if (func_ov002_02209f64((char *) a + 0x0a38) != 0) {
        return;
    }
    func_ov002_02208098(a, *(unsigned char *) ((char *) a + 0x1a7e));
    func_ov141_0229abc0(a);
}
