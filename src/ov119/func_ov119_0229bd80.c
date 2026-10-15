/* func_ov119_0229bd80 @ 0x0229bd80, 0x3c bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220909c(void *);
extern void func_ov002_022096d8(void *, int);
extern int func_0208e4bc(void *);
extern void func_ov119_0229b9a4(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);

void func_ov119_0229bd80(void *p)
{
    if (func_ov002_0220909c((char *) p + 0xDC) != 0) {
        func_ov002_022096d8((char *) p + 0xDC, 0);
        if (func_0208e4bc((char *) p + 0xDA8) != 0) {
            func_ov119_0229b9a4(p);
        }
        func_ov002_02208098(p, 0xC);
    }
}
