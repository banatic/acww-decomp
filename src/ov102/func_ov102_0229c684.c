/* func_ov102_0229c684 @ 0x0229c684, 0xbc bytes, Thumb, module ov102
 * mwccarm 1.2/base -O1,s
 */

extern int func_ov002_0220889c(int key);
extern int func_ov002_022088ac(int key);
extern int func_ov002_022088cc(int key);
extern int func_ov002_022088bc(int key);
extern void func_ov102_0229c298(void *self, int arg);

void func_ov102_0229c684(void *self, int key, int mode)
{
    int rem = ((unsigned char *) self)[0x25a5] - 30;
    int q = 0;
    while (rem >= 3) {
        rem -= 3;
        q++;
    }

    if (func_ov002_0220889c(key)) {
        if (rem < 2) {
            unsigned char *p = (unsigned char *) self + 0x25a5;
            (*p)++;
        } else {
            func_ov102_0229c298(self, 0x20);
            ((unsigned char *) self)[0x25a5] = 5 * q + 15;
            return;
        }
    } else {
        if (func_ov002_022088ac(key)) {
            if (rem > 0) {
                unsigned char *p = (unsigned char *) self + 0x25a5;
                (*p)--;
            } else {
                ((unsigned char *) self)[0x25a5] = 5 * q + 19;
                return;
            }
        }
    }

    if (func_ov002_022088cc(key)) {
        if (q > 0) {
            unsigned char *p = (unsigned char *) self + 0x25a5;
            (*p) -= 3;
        }
        return;
    } else {
        if (func_ov002_022088bc(key)) {
            if (q < 1) {
                unsigned char *p = (unsigned char *) self + 0x25a5;
                (*p) += 3;
            } else {
                if (mode != 1) {
                    ((unsigned char *) self)[0x25a5] = 0x24;
                }
            }
        }
        return;
    }
}
