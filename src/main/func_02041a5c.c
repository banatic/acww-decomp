/* func_02041a5c @ 0x02041a5c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020ee660(void *);
extern void *func_02066a04(void *);

extern unsigned char data_020da13c[];
extern unsigned char data_020db71c[];

void *func_02041a5c(void *self)
{
    volatile unsigned int *p_field;
    p_field = (volatile unsigned int *) self;
    func_020ee660(self);
    *p_field = (unsigned int) data_020da13c;
    *p_field = (unsigned int) data_020db71c;
    func_02066a04((char *) self + 0x54);
    return self;
}
