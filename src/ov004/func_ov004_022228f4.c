/* func_ov004_022228f4 @ 0x022228f4, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_022228f4(int result);
extern int func_0201b790(void *arg0);

int func_ov004_022228f4(int result)
{
    if (func_0201b790((void *) result) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
