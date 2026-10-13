/* func_0209fc40 @ 0x0209fc40, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f3c20[3];

void func_0209fc40(unsigned char value)
{
    int i;
    unsigned char temp;

    for (i = 0; i < 2; i++) {
        temp = data_021f3c20[i + 1];
        data_021f3c20[i] = temp;
    }
    data_021f3c20[2] = value;
}
