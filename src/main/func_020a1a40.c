/* func_020a1a40 @ 0x020a1a40, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02050974(void *);
extern void func_02050948(void *);
extern int func_020509a8(void *, unsigned int, unsigned int, unsigned int);
extern unsigned short func_02050920(unsigned short *, int);
extern int func_0209f180(unsigned char *);
extern void MI_CpuFill8(void *, int, int);
extern int data_021c8188;
extern int data_020d1c20[];
extern int data_020d1bf0[];
extern int data_020d1c08[];

int func_020a1a40(int a, void *b)
{
    int r;
    int v7;
    int v6;
    int t;

    r = func_02050974(&data_021c8188);
    v7 = data_020d1c20[a];
    v6 = data_020d1bf0[a];
    if (r == 4) {
        MI_CpuFill8(b, 0, v6);
        func_020509a8(&data_021c8188, (unsigned int) b, v6, v7);
    } else {
        if (r != 3) {
            func_02050948(&data_021c8188);
            t = func_02050920((unsigned short *) b, data_020d1c08[a]);
            if (func_0209f180((unsigned char *) b) == 0) {
                return 4;
            }
            if (t == 0) {
                return 0;
            }
            return 4;
        }
        if (r == 1) {
            func_02050948(&data_021c8188);
            return 1;
        }
    }
    return 3;
}
