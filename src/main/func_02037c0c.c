/* func_02037c0c @ 0x02037c0c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021c5910;
extern unsigned char *data_021c590c;

unsigned char func_02037c0c(unsigned int index)
{
    if (index < data_021c5910) {
        return data_021c590c[index];
    }
    return 0;
}
