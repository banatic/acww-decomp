/* func_0208f6e8 @ 0x0208f6e8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee660(void *p);

extern unsigned char data_020da13c[];
extern unsigned char data_020e241c[];

void *func_0208f6e8(void *p)
{
    volatile void **ptr = (volatile void **) p;
    func_020ee660(p);
    *ptr = (void *) data_020da13c;
    *ptr = (void *) data_020e241c;
    return p;
}
