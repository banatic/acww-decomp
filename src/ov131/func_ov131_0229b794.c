/* func_ov131_0229b794 @ 0x0229b794, 0x50 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe54(void *);
extern void func_ov002_02209eb8(char *);
extern int func_ov131_0229ad44(void *, int);
extern int func_ov002_02207f60(void *);
extern void func_ov002_0220ad18(char *, int);
extern void func_ov130_02299de8(char *, int);

int func_ov131_0229b794(void *param0)
{
    if (func_0206fe54(param0)) {
        func_ov002_02209eb8((char *) param0 + 0x94);
    }
    if (!func_ov131_0229ad44(param0, 1)) {
        return 0;
    } else {
        int tmp1;
        int tmp2;
        tmp1 = func_ov002_02207f60(param0);
        func_ov002_0220ad18((char *) param0 + 0xf8, tmp1);
        tmp2 = func_ov002_02207f60(param0);
        func_ov130_02299de8((char *) param0 + 0x2c4, tmp2);
        return 1;
    }
}
