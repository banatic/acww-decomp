/* func_ov142_0229bbf4 @ 0x0229bbf4, 0x40 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(int *, int);
extern void func_ov002_02208090(int *, int);
extern void func_ov002_02207eb4(int *, int, int);
extern int func_ov002_0220a924(int *, int);
extern int func_ov002_02207f60(int *);

void func_ov142_0229bbf4(int *param)
{
    if (func_ov002_02207f3c(param, -1)) {
        func_ov002_02208090(param, 5);
        func_ov002_02207eb4(param, 0, 0);
        func_ov002_0220a924(param + 101, 0x22);
    }
    param[38] = func_ov002_02207f60(param);
}
