/* func_0207a188 @ 0x0207a188, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(char *ptr);
extern int func_02003704(int val);

void func_0207a188(char *arr, char *data)
{
    int i;
    for (i = 0; i < 8; i++) {
        if (func_02003704(func_0208150c(data))) {
            arr[i] = i;
        } else {
            arr[i] = -1;
        }
        data += 0x7ec;
    }
}
