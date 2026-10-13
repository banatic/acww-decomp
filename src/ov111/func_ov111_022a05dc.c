/* func_ov111_022a05dc @ 0x022a05dc, 0xec bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *);
extern int func_ov002_02208008(void *);
extern int func_ov095_02299a54(void *, int);
extern void func_ov002_0220a2b4(void *);
extern void func_ov002_0220a254(void *);
extern int func_ov090_02299078(int);
extern int func_ov090_02299098(int);
extern void func_ov002_02208098(void *, int);
extern void func_ov111_0229f164(void *);
extern void func_ov111_0229efc8(void *, int);
extern void func_ov111_022a09f8(void *, int, int);
extern int func_ov111_0229f3ac(void *);
extern int func_ov111_0229f358(void *);
extern int func_ov111_0229f24c(void *);
extern void func_ov111_022a0204(void *);
extern unsigned short data_021fbe40[];

void func_ov111_022a05dc(void *p)
{
    int res2;
    int r;
    if (func_ov002_02208014(p) != 0) {
        func_ov111_022a0204(p);
        return;
    }
    res2 = func_ov002_02208008(p);
    r = func_ov095_02299a54((char *) p + 0xac, res2);
    switch (r) {
        case 1:
            func_ov002_0220a2b4((char *) p + 0x3d38);
            func_ov111_0229f164(p);
            break;
        case 2:
            func_ov002_0220a254((char *) p + 0x3d38);
            func_ov111_0229f164(p);
            break;
        case 4:
            func_ov002_0220a2b4((char *) p + 0x3d38);
            func_ov111_0229efc8(p, 2);
            func_ov002_02208098(p, 9);
            func_ov111_0229f164(p);
            break;
        case 0:
        case 3:
        default: {
            unsigned short v;
            if (func_ov111_0229f3ac(p) != 0) {
                return;
            }
            if (func_ov111_0229f358(p) != 0) {
                return;
            }
            if (func_ov111_0229f24c(p) != 0) {
                return;
            }
            v = data_021fbe40[1];
            if (v & 0x100) {
                int x = func_ov090_02299078(4);
                func_ov111_022a09f8(p, x, 0);
            } else if (v & 0x200) {
                int y = func_ov090_02299098(4);
                func_ov111_022a09f8(p, y, 0);
            }
            break;
        }
    }
}
