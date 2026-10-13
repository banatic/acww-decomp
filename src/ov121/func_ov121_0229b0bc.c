/* func_ov121_0229b0bc @ 0x0229b0bc, 0x26 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov121_02299ad8(void *p, unsigned char b, unsigned short h);
extern int func_ov002_02208098(void *p, int arg);

int func_ov121_0229b0bc(void *p)
{
    int r = func_ov121_02299ad8(p, *(unsigned char *) ((char *) p + 0xb7), *(unsigned short *) ((char *) p + 0xa0));
    if (r != 0) {
        r = func_ov002_02208098(p, 0x12);
    }
    return r;
}
