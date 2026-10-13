/* func_ov113_0229a194 @ 0x0229a194, 0x24 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f64(void *);
extern void func_ov002_02208098(void *, unsigned char);

void func_ov113_0229a194(void *arg0)
{
    if (!func_ov002_02209f64((char *) arg0 + 0x2b20)) {
        func_ov002_02208098(arg0, *(unsigned char *) ((char *) arg0 + 0x9c));
    }
}
