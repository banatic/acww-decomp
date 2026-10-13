/* func_ov111_022a05b0 @ 0x022a05b0, 0x2c bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov111_022a0bcc(void *);
extern int func_ov002_02209f64(void *);
extern void func_ov002_02208098(void *, unsigned char);

void func_ov111_022a05b0(void *r0)
{
    void *r4 = r0;
    if (func_ov002_02209f64((char *) r4 + 0x3d38) == 0) {
        func_ov002_02208098(r4, *(unsigned char *) ((char *) r4 + 0x98));
        func_ov111_022a0bcc(r4);
    }
}
