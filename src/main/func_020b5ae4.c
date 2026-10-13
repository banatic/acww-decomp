/* func_020b5ae4 @ 0x020b5ae4, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *p);
extern void func_020edf54(void *p);

extern unsigned char data_020da13c[];
extern unsigned char data_020e3c94[];
extern unsigned char data_020e5408[];

void *func_020b5ae4(void *p)
{
    *(unsigned int *) p = (unsigned int) data_020e5408;
    *(unsigned int *) p = (unsigned int) data_020e3c94;
    *(unsigned int *) p = (unsigned int) data_020da13c;
    func_020ee62c(p);
    func_020edf54(p);
    return p;
}
