/* func_ov104_0229d304 @ 0x0229d304, 0x74 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov104_0229c364(void *, int);
extern void func_ov104_0229c344(void *, int);
extern int func_ov104_0229d3ac(void *);
extern int func_ov104_0229d39c(void *);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_ov002_0220a05c(void *, int, int, int, int);
extern void func_ov002_02208098(void *, int);

void func_ov104_0229d304(void *param)
{
    int v1, v2;
    if (func_ov104_0229c364(param, 8) != 0) {
        v1 = func_ov104_0229d3ac(param);
        v2 = func_ov104_0229d39c(param);
        func_ov002_0220a0b4((char *) param + 0x24a0, v1, v2);
        func_ov104_0229c344(param, 8);
    } else {
        v1 = func_ov104_0229d3ac(param);
        v2 = func_ov104_0229d39c(param);
        func_ov002_0220a05c((char *) param + 0x24a0, v1, v2, 3, 1);
        *(unsigned char *) ((char *) param + 0xbb) = *(unsigned char *) ((char *) param + 0x8d);
        func_ov002_02208098(param, 13);
    }
}
