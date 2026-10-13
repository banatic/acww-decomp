/* func_ov107_0229d720 @ 0x0229d720, 0x44 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov107_0229d054(void *p0, unsigned char p1);
extern void func_ov107_0229dea4(void *p0);
extern int func_ov002_02209f64(void *p0);
extern int func_ov002_02208098(void *p0, unsigned char p1);

void func_ov107_0229d720(void *p0)
{
    if (func_ov002_02209f64((char *) p0 + 0x22b4) == 0) {
        func_ov002_02208098(p0, *(unsigned char *) ((char *) p0 + 0xbb));
        if (*(unsigned char *) ((char *) p0 + 0xbb) == 5) {
            func_ov107_0229d054(p0, *(unsigned char *) ((char *) p0 + 0xb8));
        }
        func_ov107_0229dea4(p0);
    }
}
