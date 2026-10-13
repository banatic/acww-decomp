/* func_ov130_0229a254 @ 0x0229a254, 0x24 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov130_0229a1dc(void *);
extern void func_ov130_0229a17c(void *, unsigned char);
extern void func_ov130_02299d48(void *);

void func_ov130_0229a254(void *param)
{
    func_ov130_0229a1dc(param);
    func_ov130_0229a17c(param, *(unsigned char *) ((char *) param + 4));
    *(unsigned char *) ((char *) param + 2) = 0xd;
    *(unsigned char *) ((char *) param + 3) = 5;
    func_ov130_02299d48(param);
}
