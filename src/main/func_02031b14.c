/* func_02031b14 @ 0x02031b14, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_01ffcb2c(void);
extern unsigned char data_020c9084[];

int func_02031b14(void)
{
    int result;
    int index;

    index = func_01ffcb2c();
    if (index < 0x7c) {
        result = data_020c9084[index * 30];
    } else {
        result = 0;
    }
    return result;
}
