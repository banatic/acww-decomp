/* func_02011ed4 @ 0x02011ed4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020c80b8[];
extern int func_020b65c4(void);

unsigned char func_02011ed4(void)
{
    unsigned char result;
    int index;

    index = func_020b65c4();
    result = data_020c80b8[index];
    return result;
}
