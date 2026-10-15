/* func_02083640 @ 0x02083640, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02078adc(void *, int);

void func_02083640(void *arg0, int argument1)
{
    unsigned char *ptr = (unsigned char *) arg0;
    func_02078adc(ptr + 4, (int) argument1);
    *ptr = 1;
}
