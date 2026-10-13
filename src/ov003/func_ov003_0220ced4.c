/* func_ov003_0220ced4 @ 0x0220ced4, 0x94 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_020eaa6c(void *p, void *q);
extern int func_020e8ed8(int a, int b);
extern void func_0200fa1c(void *out, void *a, void *b, short *c, const void *data);
extern int func_02031614(void *p);
extern char data_ov003_02238124[];
extern char data_ov003_0223810c[];

int func_ov003_0220ced4(void *p1, void *p2, void *p3)
{
    short local_short;
    int buf2[3];
    int buf1[3];
    int ret;

    if (func_020eaa6c(p3, (char *) p1 + 0x5c) != 0) {
        local_short = *(short *) ((char *) p1 + 0x8e);
    } else {
        local_short = (short) func_020e8ed8(*(int *) p3 - *(int *) ((char *) p1 + 0x5c),
                                            *(int *) ((char *) p3 + 8) - *(int *) ((char *) p1 + 0x64));
    }

    func_0200fa1c(buf1, p1, (char *) p1 + 0x5c, &local_short, data_ov003_02238124);
    ((int *) p2)[0] = buf1[0];
    ((int *) p2)[1] = buf1[1];
    ((int *) p2)[2] = buf1[2];

    ret = func_02031614(p2);

    func_0200fa1c(buf2, p1, (char *) p1 + 0x5c, &local_short, data_ov003_0223810c);

    if (ret != 0) {
        if (func_02031614(buf2) != 0) {
            return 1;
        }
    }
    return 0;
}
