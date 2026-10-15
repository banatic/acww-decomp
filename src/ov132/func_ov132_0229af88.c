/* func_ov132_0229af88 @ 0x0229af88, 0x70 bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099734(int);
extern int func_02098cc0(int, int, int);
extern void func_ov132_0229af54(void *, int);
extern void func_0206fdd4(void *, int, int, int, int, int);
extern void func_ov132_0229b068(void *);

void func_ov132_0229af88(void *param)
{
    if (func_02098cc0(func_02099734((int) func_020984e8()), 1, 0) == 0) {
        func_ov132_0229af54(param, 0xf);
        return;
    } else {
        ((char *) param)[0x1505] = 0x36;
        func_0206fdd4((char *) param + 0x500, 6, 0xc, 0x19, 0xf, 7);
        func_0206fdd4((char *) param + 0xd00, 6, 0xc, 0x19, 0xf, 7);
        func_ov132_0229b068(param);
    }
}
