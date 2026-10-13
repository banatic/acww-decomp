/* func_ov002_02208594 @ 0x02208594, 0x52 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220880c(void *);
extern void func_02001b6c(int);
extern void func_02001ba4(int);
extern void func_ov002_02208620(void *, int);
extern void func_ov002_022085e8(void *, int);

int func_ov002_02208594(void *self, int q)
{
    unsigned char kind;

    if (func_ov002_0220880c(self)) {
        switch (q) {
            case 0:
                func_02001b6c(1);
                break;
            case 1:
                func_02001ba4(1);
                break;
        }
        return 1;
    }

    kind = ((unsigned char *) self)[0x18];
    switch (kind) {
        case 0:
        case 1:
            func_ov002_02208620(self, q);
            break;
        default:
            func_ov002_022085e8(self, q);
            break;
    }
    return 0;
}
