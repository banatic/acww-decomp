/* func_0209fc00 @ 0x0209fc00, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f3c20[3];

void func_0209fc00(unsigned char value)
{
    int index;
    int i;

    index = 0xFF;
    for (i = 0; i < 3; i++) {
        if (data_021f3c20[i] == value) {
            index = i;
            break;
        }
    }

    if (index != 0xFF) {
        while (index < 2) {
            data_021f3c20[index] = data_021f3c20[index + 1];
            index++;
        }
        data_021f3c20[2] = 0xFF;
    }
}
