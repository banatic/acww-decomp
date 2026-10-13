/* func_02050e74 @ 0x02050e74, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02050ef4(void *);
extern int func_02050edc(void *);

unsigned char func_02050e74(void *arg0)
{
    unsigned char r5;
    void *r4 = arg0;
    r5 = *(unsigned char *) ((char *) r4 + 0x39);
    if (func_02050ef4(r4)) {
        r4 = (char *) r4 + 0x3b;
        r5 = *(unsigned char *) r4;
    } else {
        if (func_02050edc(r4)) {
            r4 = (char *) r4 + 0x3d;
            r5 = *(unsigned char *) r4;
        }
    }
    return r5;
}
