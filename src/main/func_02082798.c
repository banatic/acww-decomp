/* func_02082798 @ 0x02082798, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02082854(void *self, unsigned short *p);

int func_02082798(void *self, unsigned short key)
{
    unsigned short tmp = 0xfff1;
    int res = 0;
    int idx;

    tmp = (unsigned short) ((key & 0xfff) | 0xd000);
    idx = func_02082854(self, &tmp);
    if (idx >= 0 && idx < 4) {
        res = *(unsigned int *) ((unsigned char *) self + (idx << 3) + 0x40);
    }
    return res;
}
