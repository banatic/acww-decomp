/* func_02031b38 @ 0x02031b38, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_01ffcb2c(int, int);
extern unsigned char data_020c9080[];

unsigned char func_02031b38(int argument0, int argument1)
{
    int idx;

    idx = func_01ffcb2c((int) argument0, (int) argument1);
    if (idx < 124) {
        return data_020c9080[idx * 30];
    } else {
        return 0;
    }
}
