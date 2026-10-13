/* func_020a6294 @ 0x020a6294, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;

extern int func_02073dd4(void *g, int dir);
extern int func_020a72d0(int dir);
extern int func_020a6338(void *self);
extern int func_02073918(void *g, int dir);
extern int func_020a7330(int dir);
extern int func_020b65c4(int x);
extern int func_020a7300(int dir);
extern int func_020a6c98(int x);
extern void func_02073820(void *g);
extern void func_02073770(void *g, int a, int dir);
extern void func_020a633c(void *self, int dir);

void func_020a6294(void *self)
{
    int best = 4;
    int dir = 3;
    void *g = data_020ccf94;

    for (; dir >= 0; dir--) {
        if (func_02073dd4(g, dir) != 0 && func_020a72d0(dir) != 0) {
            best = dir;
            break;
        }
    }

    if (best != func_020a6338(self)) {
        if (best < 4) {
            if (func_02073918(g, best) == 0) {
                int v = func_020a7330(best);
                if (v == func_020b65c4(v)) {
                    int r = func_020a7300(best);
                    if (r != 0) {
                        if (func_020a6c98(func_020b65c4(r)) == 0) {
                            void *g2 = data_020ccf94;
                            func_02073820(g2);
                            func_02073770(g2, 0xd, best);
                        }
                    }
                }
            }
            func_020a633c(self, best);
        } else {
            func_020a633c(self, 4);
        }
    }
}
