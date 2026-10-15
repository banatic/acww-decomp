/* func_02097864 @ 0x02097864, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02098a18(int object);
extern unsigned char *func_02097e14(void *record);
extern unsigned char func_02065ec0(unsigned char *buffer);

int func_02097864(int param)
{
    if (param == 0) {
        param = func_020984e8();
    }
    if (func_02065ec0(func_02097e14((void *) func_02098a18(param))) != 0) {
        return 1;
    } else {
        return 0;
    }
}
