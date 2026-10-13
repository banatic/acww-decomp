/* func_0209dc10 @ 0x0209dc10, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d1b04[];

int func_0209dc10(unsigned char *arr)
{
    unsigned char local[2];
    unsigned short value;
    unsigned short *p;
    int i;
    int result = 0;

    local[1] = arr[1];
    local[0] = arr[0];
    value = *(unsigned short *) local;
    for (p = (unsigned short *) data_020d1b04, i = 0; i < 0x13; p++, i++) {
        if (value <= *p) {
            result = i;
            break;
        }
    }
    return result;
}
