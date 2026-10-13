/* func_020a88ec @ 0x020a88ec, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020da6c4;
extern char data_020e3d7c;
extern void func_020a9b50(void *);

void *func_020a88ec(void *p)
{
    volatile unsigned int *pp = (volatile unsigned int *) p;
    *pp = (unsigned int) &data_020da6c4;
    *pp = (unsigned int) &data_020e3d7c;
    func_020a9b50((char *) p + 4);
    return p;
}
