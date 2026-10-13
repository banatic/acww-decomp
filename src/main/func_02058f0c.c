/* func_02058f0c @ 0x02058f0c, 0x46 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02059674(void *p, int flag);
extern void func_0205967c(void *p, void *buf);
extern void func_020eaca0(void *out, void *src, void *tmp);

void func_02058f0c(void *self)
{
    int tmp[3];
    int out[3];

    func_02059674(self, 0);
    func_0205967c(self, tmp);
    func_020eaca0(out, (char *) self + 0x60, tmp);

    ((int *) ((char *) self + 0x84))[0] = out[0];
    ((int *) ((char *) self + 0x88))[0] = out[1];
    ((int *) ((char *) self + 0x8c))[0] = out[2];

    *(short *) ((char *) self + 0xd6) = 0;
}
