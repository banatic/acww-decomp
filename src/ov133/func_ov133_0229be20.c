/* func_ov133_0229be20 @ 0x0229be20, 0x2c bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov133_0229c420(void *);
extern int func_ov002_02209f64(void *);
extern int func_ov002_02208098(void *, unsigned char);

void func_ov133_0229be20(void *r0)
{
    if (func_ov002_02209f64((char *) r0 + 0x11c) == 0) {
        func_ov002_02208098(r0, *(unsigned char *) ((char *) r0 + 0x9b));
        func_ov133_0229c420(r0);
    }
}
