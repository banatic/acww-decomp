/* func_020a99d8 @ 0x020a99d8, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FS_CloseFile(void *ptr);

extern unsigned char data_021f43ec;

void func_020a99d8(void *arg)
{
    unsigned char *p;
    unsigned char val;

    p = (unsigned char *) arg;
    if (p[0x8c] != 0) {
        FS_CloseFile((void *) ((unsigned char *) arg + 0x44));
        p[0x8c] = 0;
        val = data_021f43ec;
        p[0x8d] = val;
    }
}
