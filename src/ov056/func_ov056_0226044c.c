/* func_ov056_0226044c @ 0x0226044c, 0x20 bytes, Thumb, module ov056
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *p);

extern unsigned char data_020da13c[];
extern unsigned char data_ov056_022604b0[];

void *func_ov056_0226044c(void *p)
{
    *(volatile unsigned int *) p = (unsigned int) data_ov056_022604b0;
    *(volatile unsigned int *) p = (unsigned int) data_020da13c;
    func_020ee62c(p);
    return p;
}
