/* func_02063f40 @ 0x02063f40, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205be20(void);
extern int func_0205be2c(void);
extern int FX_Div(int a, int b);
extern unsigned char data_020de63c[];

unsigned char func_02063f40(unsigned int param)
{
    int a = func_0205be20();
    int sum = a + func_0205be2c();
    unsigned char byte = (unsigned char) FX_Div(sum, 0xA000);
    unsigned char arr[3];
    unsigned char *p = arr;
    arr[0] = data_020de63c[0];
    arr[1] = data_020de63c[1];
    arr[2] = data_020de63c[2];
    arr[0] = 60 - byte;
    arr[2] = byte + 10;
    if (param < 3) {
        return p[param];
    } else {
        return arr[0];
    }
}
