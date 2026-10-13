/* func_ov004_0221e144 @ 0x0221e144, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0221e144(void);
extern int func_0201b790(void);

int func_ov004_0221e144(void)
{
    int result;
    if (func_0201b790() != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
