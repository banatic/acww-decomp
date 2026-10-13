/* func_02062300 @ 0x02062300, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6e8(void *ptr);
extern void *func_0206e7bc(void *ptr, unsigned int index);

extern unsigned char data_021cb5e0[];

unsigned char func_02062300(unsigned short *ptr)
{
    unsigned int masked;
    unsigned int index;
    void *tmp;
    void *result;

    masked = *ptr & 0xfff;
    index = (masked < 0x56e) ? masked : 0x56d;
    tmp = func_0206e6e8((void *) data_021cb5e0);
    result = func_0206e7bc(tmp, index);
    if (result != 0) {
        return ((unsigned char *) result)[1];
    } else {
        return 0;
    }
}
