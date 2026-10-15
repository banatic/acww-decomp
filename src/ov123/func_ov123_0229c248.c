/* func_ov123_0229c248 @ 0x0229c248, 0x94 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *p, int a);
extern void func_ov002_02207eb4(void *p, int a, int b);
extern int func_ov123_02299650(void *p, int a);
extern int func_ov002_0220aacc(void *p, int a);
extern void func_ov002_02208090(void *p, int a);
extern void func_ov123_02299684(void *p);
extern void func_ov123_02299630(void *p, int a);
extern void func_ov123_0229c044(void *p);

void func_ov123_0229c248(void *param)
{
    if (func_ov002_02207f3c(param, -1) != 0) {
        func_ov002_02207eb4(param, 0, 0);
        if (func_ov123_02299650(param, 8) != 0) {
            func_ov002_0220aacc((char *) param + 0x5030, 0x87);
        } else {
            func_ov002_0220aacc((char *) param + 0x5030, 0x22);
        }
        func_ov002_02208090(param, 8);
    }

    if (func_ov123_02299650(param, 0x400) != 0) {
        if (*(int *) ((char *) param + 0x98) < 0x10) {
            *(int *) ((char *) param + 0x98) = *(int *) ((char *) param + 0x98) + 2;
        } else {
            func_ov123_02299684(param);
            *(int *) ((char *) param + 0x98) = 0x10;
            func_ov123_02299630(param, 0x400);
        }
    }
    func_ov123_0229c044(param);
}
