/* func_02097864 @ 0x02097864, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020984e8(void);
extern void func_02098a18(void);
extern void func_02097e14(void);
extern int func_02065ec0(void);

int func_02097864(int param)
{
    if (param == 0) {
        func_020984e8();
    }
    func_02098a18();
    func_02097e14();
    if (func_02065ec0() != 0) {
        return 1;
    } else {
        return 0;
    }
}
