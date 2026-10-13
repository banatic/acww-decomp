/* func_02060da8 @ 0x02060da8, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02060e78(void *);
extern unsigned short data_020cc9ec[][5];

extern unsigned char data_021ebcd4[];

unsigned short func_02060da8(int unused, int b)
{
    int x;
    if (b == -1) {
        goto L1;
    }
    x = func_02060e78((void *) data_021ebcd4);
    if (x >= 7) {
        goto L2;
    }
    return data_020cc9ec[x][b];
L2:
    return 0x1002;
L1:
    return 0x1002;
}
