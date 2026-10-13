/* func_020655c4 @ 0x020655c4, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern unsigned int data_021cd864;
extern unsigned int func_020bbef4(void);

unsigned int func_020655c4(unsigned int param0)
{
    unsigned int result;
    unsigned int flag;

    flag = (data_020e54a8 == 1) ? 1 : 0;
    if (flag != 0) {
        if (param0 == 0) {
            result = *(unsigned char *) (*(unsigned int *) &data_021cd864 + 0x178);
        } else {
            result = func_020bbef4();
        }
    } else {
        result = func_020bbef4();
    }
    return result;
}
