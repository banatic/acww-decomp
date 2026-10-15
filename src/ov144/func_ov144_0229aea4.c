/* func_ov144_0229aea4 @ 0x0229aea4, 0x30 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *, int);
extern void func_020027f0(int);
extern unsigned char *func_ov002_022080a0(void *, unsigned char value);
extern void func_ov144_0229ae64(void *);

void func_ov144_0229aea4(void *param)
{
    if (func_ov002_02207f3c(param, 0) != 0) {
        func_020027f0(6);
        func_020027f0(4);
        func_ov002_022080a0(param, 5);
    } else {
        func_ov144_0229ae64(param);
    }
}
