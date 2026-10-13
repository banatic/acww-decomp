/* func_02035e68 @ 0x02035e68, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int *func_02035e68(void);

extern unsigned char data_021c526c[];

unsigned int *func_02035e68(void)
{
    unsigned int *ptr;
    unsigned int offset;

    ptr = *(unsigned int **) data_021c526c;
    offset = 0x264;
    return (unsigned int *) ((char *) ptr + offset);
}
