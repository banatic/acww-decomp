/* func_ov096_0229ec4c @ 0x0229ec4c, 0x44 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c60;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c5c;
extern unsigned char data_021f6c54;

int func_ov096_0229ec4c(void *receiver)
{
    int a;
    int b;
    int c;
    int d;

    a = data_021f6c60;
    b = data_021f6c58;
    c = a - b;
    if (c < 0) {
        c = -c;
    }
    if (c > 8) {
        return 1;
    }

    a = data_021f6c5c;
    b = data_021f6c54;
    c = a - b;
    if (c < 0) {
        c = -c;
    }
    if (c > 8) {
        return 1;
    }

    return 0;
}
