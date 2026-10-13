/* func_0207cd4c @ 0x0207cd4c, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6694(int);
extern int func_020b66c4(int);
extern int func_0207cf74(int);
extern int func_0207cec0(int, int);

int func_0207cd4c(int param1, int param2)
{
    int result;
    unsigned char byte;
    int temp;

    result = 0;
    byte = (unsigned char) param2;
    if (func_020b6694(byte) != 0) {
        temp = func_020b66c4(byte);
        if (func_0207cf74(temp) != 0) {
            result = func_0207cec0(param1, temp);
        }
    }
    return result;
}
