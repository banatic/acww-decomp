/* func_02038bfc @ 0x02038bfc, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020eba08();
extern int func_020ec1e8();
extern int data_021c5938;
extern unsigned char data_021c5934;

void func_02038bfc(void)
{
    int a;
    int b;
    int val;

    a = func_020eba08();
    data_021c5938 = a;

    b = func_020ec1e8();

    switch (b) {
        case 3:
        case 4:
            val = 1;
            break;
        default:
            val = 0;
            break;
    }

    data_021c5934 = (unsigned char) val;
}
