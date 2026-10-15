/* func_ov119_0229b38c @ 0x0229b38c, 0x4e bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov119_0229ac80(void);
extern void func_ov119_0229bba8(int, int);
extern char *func_ov119_0229ae50(void);
extern void func_02077c40(char *);
extern void func_0206fc80(unsigned char);
extern int func_ov119_0229c608(int, int);
extern void func_ov119_0229c5f4(int);

void func_ov119_0229b38c(int param)
{
    int idx = func_ov119_0229ac80();
    if (idx == -1) {
        func_ov119_0229bba8(param, 0x13);
    } else {
        char *base;
        asm {
            mov r0, param
        }
        base = func_ov119_0229ae50();
        func_02077c40(base + 0x24 * idx);
        func_0206fc80((unsigned char) idx);
        func_ov119_0229c608(param, 0xe);
        func_ov119_0229c5f4(param);
    }
}
