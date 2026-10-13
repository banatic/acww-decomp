/* func_02084840 @ 0x02084840, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02084890(void);
extern int func_020b65c4(void);
extern int func_02084d34(unsigned int, unsigned int, unsigned int);
extern unsigned char data_020e54a8;
extern unsigned int data_020e1b84;
extern unsigned int data_020e1d8c;
extern unsigned int data_020d0644;

int func_02084840(void *param)
{
    if (func_02084890() != 0) {
        if (param != 0) {
            unsigned int ok = (data_020e54a8 == 0) ? 1 : 0;
            if (ok == 0) {
                goto ret0;
            }
            if (func_020b65c4() == 0x2c) {
                goto ret0;
            }
        }
        return func_02084d34((unsigned int) &data_020e1b84, (unsigned int) &data_020e1d8c, data_020d0644);
    }
ret0:
    return 0;
}
