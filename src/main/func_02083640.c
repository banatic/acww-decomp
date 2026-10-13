/* func_02083640 @ 0x02083640, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02078adc(void *);

void func_02083640(void *arg0)
{
    unsigned char *ptr = (unsigned char *) arg0;
    func_02078adc(ptr + 4);
    *ptr = 1;
}
