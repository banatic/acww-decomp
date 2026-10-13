/* func_020a8718 @ 0x020a8718, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_020a87c8(void *arg0, int arg1);

void func_020a8718(void *arg0, unsigned char *arg1, unsigned char *arg2)
{
    unsigned char *r4;
    unsigned char *r6;
    void *r5;
    unsigned char temp;

    r5 = arg0;
    r4 = arg1;
    r6 = arg2;

    temp = func_020a87c8(*(void **) ((unsigned int) r5 + 0xc), 0);
    *r4 = temp;
    temp = func_020a87c8(*(void **) ((unsigned int) r5 + 0xc), 1);
    *r6 = temp;
}
