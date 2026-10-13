/* func_ov119_0229bfdc @ 0x0229bfdc, 0x2c bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov119_0229c75c(void *);
extern int func_ov002_02209f64(void *);
extern void func_ov002_02208098(void *, unsigned char);

void func_ov119_0229bfdc(void *arg)
{
    if (!func_ov002_02209f64((char *) arg + 0xda8)) {
        func_ov002_02208098(arg, *(unsigned char *) ((char *) arg + 0x9f));
        func_ov119_0229c75c(arg);
    }
}
