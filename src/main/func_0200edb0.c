/* func_0200edb0 @ 0x0200edb0, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65b8(void);
extern int func_02073dd4(unsigned int, int);
extern int func_0209658c(void *, int, int);
extern unsigned int data_020ccf94;

int func_0200edb0(void)
{
    int status;
    int i;
    int local;
    unsigned int base;

    status = func_020b65b8();

    if (status == 0xc || status == 0xd || status == 0xe || (unsigned char) (status + 0xd2) <= 1) {
        i = 0;
        base = data_020ccf94;
        while (i < 4) {
            if (func_02073dd4(base, i) != 0) {
                if (func_0209658c(&local, -1, i) == 0) {
                    return 1;
                }
            }
            i++;
        }
    }

    return 0;
}
