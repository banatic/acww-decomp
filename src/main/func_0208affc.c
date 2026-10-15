/* func_0208affc @ 0x0208affc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020ee660(void *p);

extern unsigned char data_020da13c[];
extern unsigned char data_020e2288[];

void *func_0208affc(void *p)
{
    func_020ee660(p);
    *(void **) p = (void *) data_020da13c;
    *(void **) p = (void *) data_020e2288;
    return p;
}
