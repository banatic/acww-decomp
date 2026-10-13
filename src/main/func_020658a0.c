/* func_020658a0 @ 0x020658a0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern unsigned char data_020ccc48[];

int func_020658a0(void)
{
    int result = 0xf;
    unsigned char val = data_020ccc48[func_020b65c4()];
    switch (val) {
        case 2:
        case 3:
            result = 1;
            break;
    }
    return result;
}
