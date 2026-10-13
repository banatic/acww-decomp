/* func_020a71ec @ 0x020a71ec, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern unsigned char data_021f4320[];
extern int func_02073dd4(int a, int b);
extern void func_020a7738(const unsigned char *src, unsigned char *out0, unsigned char *out1, unsigned char *out2);
int func_020a71ec(int param)
{
    int n = 3;
    int i;
    int result = 4;
    int x;
    unsigned char arr[3];
    i = n;
    x = data_020ccf94;
    while (i >= 0) {
        if (func_02073dd4(x, i) != 0) {
            func_020a7738(&data_021f4320[n * i], &arr[0], &arr[1], &arr[2]);
            if (arr[0] == param && arr[1] != 0 && arr[2] == 0) {
                result = i;
                break;
            }
        }
        i--;
    }
    return result;
}
