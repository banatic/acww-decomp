/* func_020a1518 @ 0x020a1518, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984d4(void);
extern void func_020984e8(void);
extern char *func_02099658(void);
extern void func_02098844(char *p, int val);
extern void *func_02077c9c(char *p);
extern void *func_020508fc(char *p, int n, void *q);
extern void func_02077ca8(char *p, void *q);
extern int func_02050af8(char *dst, char *src, char *src2, int len);

extern char data_021dc7a8[];  // 0x021dc7a8
extern char data_021c8188[];  // 0x021c8188
extern char *data_020d1c20[]; // array of char*
extern unsigned char data_020e37f8;

int func_020a1518(void)
{
    char *base = data_021dc7a8; // hold in callee-saved register
    int val;
    char *b, *c;
    int diff;

    val = func_020984d4();
    func_020984e8();
    b = func_02099658();
    if (val >= 4) {
        val = data_020e37f8;
    }
    func_02098844(base + 0x14, val);
    c = func_02099658();
    func_02077ca8(b, func_020508fc(b, 0x484, func_02077c9c(b)));
    diff = c - base;
    if (func_02050af8(data_021c8188, data_020d1c20[0] + diff, b, 0x484) == 1) {
        return 1;
    }
    if (func_02050af8(data_021c8188, data_020d1c20[1] + diff, b, 0x484) == 1) {
        return 1;
    }
    return 0;
}
