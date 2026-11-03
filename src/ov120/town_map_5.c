/* town_map_5: 2 functions, module ov120
 * mwccarm 1.2/base -O4,s
 * func_ov120_0229b64c @ 0x0229b64c, 0x16 bytes, Thumb
 * func_ov120_0229b604 @ 0x0229b604, 0x48 bytes, Thumb
 */

extern void func_ov120_0229a7a8(void *arg0);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern void *func_0208e95c(int, int);
extern void func_ov120_0229a870(int);
extern void func_ov002_02207fc0(int);
extern int func_ov120_0229a448(int, int);

void func_ov120_0229b64c(void *p)
{
    func_ov120_0229a7a8((void *) p);
    func_ov002_02208098(p, 0);
}

void func_ov120_0229b604(int r0)
{
    int r4 = r0;
    func_0208e95c(r4 + 0x674, 1);
    func_ov120_0229a870(r4);
    func_ov002_02207fc0(r4);
    if (func_ov120_0229a448(r4, 0x800) != 0) {
        func_ov002_02208098((void *) r4, 9);
    } else {
        func_ov002_02208098((void *) r4, 2);
    }
}
