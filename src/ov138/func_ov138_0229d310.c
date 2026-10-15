/* func_ov138_0229d310 @ 0x0229d310, 0x54 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *);
extern int func_ov138_0229c574(void *, int);
extern int func_ov002_02207f60(void *);
extern void func_ov134_0229b220(void *, int, int);
extern void func_ov002_0220ad18(void *, int);

int func_ov138_0229d310(char *param)
{
    if (func_0206fe54() != 0) {
        func_ov002_02209eb8(param + 0x98);
    }
    if (func_ov138_0229c574(param, 1) == 0) {
        return 0;
    }
    {
        int result1;
        int result2;
        result1 = func_ov002_02207f60(param);
        func_ov134_0229b220(param + 0x2c8, 0, result1);
        result2 = func_ov002_02207f60(param);
        func_ov002_0220ad18(param + 0xfc, result2);
    }
    return 1;
}
