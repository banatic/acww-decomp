/* func_020827dc @ 0x020827dc, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02082854(void *);

int func_020827dc(void *param)
{
    int idx;
    int ret;
    char *p;

    idx = func_02082854(param);
    ret = 0;
    if (idx >= 0 && idx < 4) {
        p = (char *) param + idx * 8;
        *(unsigned int *) (p + 0x40) = 0;
        *(unsigned short *) (p + 0x44) = 0xFFF1;
        ret = 1;
    }
    return ret;
}
