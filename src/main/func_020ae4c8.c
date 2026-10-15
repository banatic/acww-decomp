/* func_020ae4c8 @ 0x020ae4c8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_020984e8(void);
extern unsigned char func_02099870(int);
extern unsigned char func_02094ffc(void *);

extern unsigned char data_021f49e8[];

unsigned char func_020ae4c8(void)
{
    unsigned char result;
    unsigned char *addr;

    if (func_02094ffc((void *) func_02099870((int) func_020984e8())) == 1) {
        addr = (unsigned char *) data_021f49e8;
        result = *addr;
    } else {
        result = 0;
    }
    return result;
}
