/* func_ov104_0229df84 @ 0x0229df84, 0x50 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(char *);
extern void func_ov002_02208098(char *, unsigned char);
extern int func_ov002_02209f9c(char *);
extern int func_ov104_0229c364(char *, int);
extern void func_ov104_0229c344(char *, int);
extern void func_ov094_022999c0(void);
extern void func_ov104_0229d528(char *);

void func_ov104_0229df84(char *obj)
{
    if (func_0208e484(obj + 0x24a0)) {
        func_ov002_02208098(obj, *(unsigned char *) (obj + 0xbb));
    }
    if (func_ov002_02209f9c((char *) ((unsigned int) obj + 0x24a0))) {
        if (func_ov104_0229c364(obj, 0x40)) {
            func_ov104_0229c344(obj, 0x40);
            func_ov094_022999c0();
        }
        func_ov104_0229d528(obj);
    }
}
