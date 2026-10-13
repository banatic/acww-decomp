/* func_0204c4e8 @ 0x0204c4e8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcf8(void *param);
extern int func_0204b42c(void *param);
extern void NNS_FndAllocFromAllocator(void *buffer, int value);
extern int func_0206266c(void *buffer);
extern void func_020051b0(void *buffer);

int func_0204c4e8(void *param)
{
    if (func_0204bcf8(param) == 1) {
        int result;
        char buffer[8];
        NNS_FndAllocFromAllocator(buffer, func_0204b42c(param));
        result = func_0206266c(buffer);
        func_020051b0(buffer);
        return result;
    }
    return 0;
}
