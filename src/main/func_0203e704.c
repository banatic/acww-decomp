/* func_0203e704 @ 0x0203e704, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203e340(void);
extern unsigned char data_021c75b8;

int func_0203e704(unsigned char *param)
{
    if (func_0203e340() != 0) {
        return 0;
    }
    {
        unsigned int flag = (data_021c75b8 == 2) ? 1 : 0;
        if (flag == 0) {
            return 0;
        } else {
            if (param[0x17] != 6) {
                return 0;
            }
            return 1;
        }
    }
}
