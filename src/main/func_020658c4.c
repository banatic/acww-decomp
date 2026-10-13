/* func_020658c4 @ 0x020658c4, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern unsigned char data_020ccc48[];

int func_020658c4(void)
{
    int ret = 15;
    switch (data_020ccc48[func_020b65c4()]) {
        case 2:
        case 3:
            ret = 1;
            break;
    }
    return ret;
}
