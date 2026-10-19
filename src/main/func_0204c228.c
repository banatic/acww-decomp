/* func_0204c228 @ 0x0204c228, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0204b2c8(void *arg);
extern int func_0204b42c(void *arg);
extern void func_0204b3cc(void *object, unsigned int value);
extern void *func_020622c4(void *ptr);
extern void func_020051b0(void *ptr);

void *func_0204c228(void *arg)
{
    void *result;
    unsigned int size;
    unsigned int local[2];

    if (func_0204b2c8(arg) != 0) {
        size = func_0204b42c(arg);
        func_0204b3cc(local, size);
        result = func_020622c4(local);
        func_020051b0(local);
        return result;
    }
    return 0;
}
