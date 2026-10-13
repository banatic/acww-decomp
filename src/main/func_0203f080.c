/* func_0203f080 @ 0x0203f080, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e8ce0(void *a, void *b);
extern void func_020ee62c(void *obj);

extern unsigned char data_0213ff78[];

extern unsigned char data_020d7244[];
extern unsigned char data_020da13c[];
extern unsigned char data_020dab34[];

void *func_0203f080(void *obj)
{
    volatile unsigned int *p = (volatile unsigned int *) obj;
    *p = (unsigned int) data_020dab34;
    *p = (unsigned int) data_020d7244;
    func_020e8ce0((void *) data_0213ff78, (char *) obj + 0x50);
    *p = (unsigned int) data_020da13c;
    func_020ee62c(obj);
    return obj;
}
