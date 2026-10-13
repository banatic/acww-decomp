/* func_ov132_0229b27c @ 0x0229b27c, 0x28 bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f64(void *);
extern int func_ov002_02208098(void *, unsigned char);
extern void func_ov132_0229b6c0(void *);

void func_ov132_0229b27c(void *r0)
{
    void *r4 = r0;
    if (func_ov002_02209f64((char *) r0 + 0x94) == 0) {
        func_ov002_02208098(r4, *(unsigned char *) ((char *) r4 + 0x1503));
        func_ov132_0229b6c0(r4);
    }
}
