/* func_020b68b0 @ 0x020b68b0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f69ec[0x20];

void func_020b68b0(int arg0, const unsigned char *src)
{
    unsigned char *dst;
    int i;

    dst = data_021f69ec;
    i = 0;
    do {
        *dst = *src;
        dst++;
        src++;
        i++;
    } while (i < 0x20);
}
