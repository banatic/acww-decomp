/* func_0203a9cc @ 0x0203a9cc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *);

extern unsigned char data_020da13c[];
extern unsigned char data_020da87c[];
extern unsigned char data_020e58cc[];

void *func_0203a9cc(void *obj)
{
    volatile unsigned int *p;
    p = (volatile unsigned int *) obj;
    *p = (unsigned int) data_020da87c;
    *p = (unsigned int) data_020e58cc;
    *p = (unsigned int) data_020da13c;
    func_020ee62c(obj);
    return obj;
}
