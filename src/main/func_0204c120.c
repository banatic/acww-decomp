/* func_0204c120 @ 0x0204c120, 0xf0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02034ce0(int *);
extern void func_0204b79c(int *, int);
extern int func_0204c878(int *);
extern void func_020051b0(int *);
extern int func_0204c210(int);
extern int func_0204b42c(int *);

int func_0204c120(int param0, int param1, int *param2)
{
    int it;
    unsigned int idx;
    int pos;
    int result;

    func_02034ce0(&it);

    if (param2 != 0) {
        *param2 = 0;
    }

    if (param1 != 0) {
        func_0204b79c(&it, 0x14fd);
        pos = func_0204c878(&it);
        if (pos < param0) {
            func_020051b0(&it);
            return 0xfff1;
        }

        for (idx = 0; idx < 0x6c; idx++) {
            func_0204b79c(&it, func_0204c210(idx));
            pos = func_0204c878(&it);
            if (pos >= param0) {
                if (param2 != 0) {
                    *param2 = pos - param0;
                }
                result = func_0204b42c(&it);
                func_020051b0(&it);
                return result;
            }
        }
    } else {
        func_0204b79c(&it, 0x1492);
        pos = func_0204c878(&it);
        if (pos > param0) {
            func_020051b0(&it);
            return 0xfff1;
        }

        for (idx = 0x6c; idx != 0; idx--) {
            func_0204b79c(&it, func_0204c210(idx - 1));
            pos = func_0204c878(&it);
            if (param0 >= pos) {
                if (param2 != 0) {
                    *param2 = param0 - pos;
                }
                result = func_0204b42c(&it);
                func_020051b0(&it);
                return result;
            }
        }
    }

    func_020051b0(&it);
    return 0xfff1;
}
