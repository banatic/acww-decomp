/* func_0204c6b8 @ 0x0204c6b8, 0x62 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcf8(int);
extern int func_0204b42c(int);
extern void NNS_FndAllocFromAllocator(void *, int);
extern int func_020629ec(void *);
extern void func_020051b0(void *);
extern int func_0204c614(int);
extern int func_0204c5ec(int);

int func_0204c6b8(int arg)
{
    int local[2];
    int ret;
    int temp;
    int result;

    ret = func_0204bcf8(arg);
    switch (ret) {
        case 1:
            temp = func_0204b42c(arg);
            NNS_FndAllocFromAllocator(local, temp);
            result = func_020629ec(local);
            func_020051b0(local);
            return result;
        case 3:
        case 4:
            if (func_0204c614(arg) != 0) {
                return 0xa7;
            } else if (func_0204c5ec(arg) != 0) {
                return 1;
            } else {
                return 0;
            }
        default:
            return 0;
    }
}
