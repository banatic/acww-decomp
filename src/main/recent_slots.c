/* recent_slots: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209fc40 @ 0x0209fc40, 0x20 bytes, Thumb
 * func_0209fc00 @ 0x0209fc00, 0x40 bytes, Thumb
 * func_0209fbec @ 0x0209fbec, 0x14 bytes, Thumb
 * func_0209fbd0 @ 0x0209fbd0, 0x1c bytes, Thumb
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

void func_0209fbec(void)
{
    int i;

    for (i = 0; i < 3; i++) {
        data_021f3c20[i] = 0xFF;
    }
}

int func_0209fbd0(void)
{
    int i;
    for (i = 2; i >= 0; i--) {
        if (data_021f3c20[i] != 0xff) {
            return data_021f3c20[i];
        }
    }
    return 4;
}
