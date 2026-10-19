/* func_0204c878 @ 0x0204c878, 0x190 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0204c878 {
    short v;
} UnkStruct_0204c878;

extern void func_02061e2c(UnkStruct_0204c878 *, void *);
extern int func_0204bcf8(UnkStruct_0204c878 *);
extern int func_0204c7c8(UnkStruct_0204c878 *);
extern int func_0204b42c(void *);
extern void func_0204b3cc(UnkStruct_0204c878 *, int);
extern int func_020628ac(UnkStruct_0204c878 *);
extern void func_020051b0(UnkStruct_0204c878 *);
extern int func_0204ca64(UnkStruct_0204c878 *);
extern int func_0204c7c0(void);
extern int func_0204ca60(int);
extern int func_0204ca48(unsigned int);
extern int func_0204ca08(UnkStruct_0204c878 *, UnkStruct_0204c878 *);
extern int func_0204bc64(UnkStruct_0204c878 *);
extern int func_02053e18(int object);

int func_0204c878(void *arg)
{
    int forwarded_value;

    UnkStruct_0204c878 a, b, c, d, e, f;
    int r;

    func_02061e2c(&a, arg);
    switch (func_0204bcf8(&a)) {
        case 1:
            if (func_0204c7c8(&a) != 0) {
                func_0204b3cc(&c, func_0204b42c(&a));
                r = 10 * func_020628ac(&c);
                func_020051b0(&c);
                func_020051b0(&a);
                return r;
            }
            if (func_0204ca64(&a) != 0) {
                func_0204b3cc(&b, func_0204ca48((unsigned int) func_0204ca60(func_0204c7c0() + 0x17254)));
                if (func_0204ca08(&a, &b) != 0) {
                    func_0204b3cc(&d, func_0204b42c(&a));
                    r = func_020628ac(&d) / 5;
                    func_020051b0(&d);
                    func_020051b0(&b);
                    func_020051b0(&a);
                    return r;
                }
                func_020051b0(&b);
            } else if (func_0204b42c(arg) == 0x1406 || func_0204b42c(arg) == 0x1407) {
                func_0204b3cc(&e, func_0204b42c(&a));
                r = 100 * func_020628ac(&e);
                func_020051b0(&e);
                func_020051b0(&a);
                return r;
            }
            func_0204b3cc(&f, func_0204b42c(&a));
            r = func_020628ac(&f);
            func_020051b0(&f);
            func_020051b0(&a);
            return r;
        case 3:
        case 4:
            if ((forwarded_value = (int) func_0204bc64(&a)) == 0x208) {
                r = 100 * func_02053e18((int) forwarded_value);
                func_020051b0(&a);
                return r;
            }
            r = func_02053e18((int) forwarded_value);
            func_020051b0(&a);
            return r;
        default:
            func_020051b0(&a);
            return 0;
    }
}
