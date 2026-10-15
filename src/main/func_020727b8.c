/* func_020727b8 @ 0x020727b8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021d0478[4];
extern unsigned char data_021d0468;

void func_020727b8(void *receiver)
{
    unsigned int i = 0;
    unsigned int v = i;
    do {
        data_021d0478[i] = (unsigned char) v;
        i++;
    } while (i < 4);
    data_021d0468 = (unsigned char) v;
}
