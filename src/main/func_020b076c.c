/* func_020b076c @ 0x020b076c, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char *base;
    unsigned int width;
    unsigned int height;
} UnkStruct_020b076c;

extern UnkStruct_020b076c *func_0204e414(void);
extern void *func_02037e0c(void *ptr, int k, int l, int zero);
extern int func_0204bb54(void *p);
extern int func_0204bb2c(void *p);
extern void func_0204f800(void *p1, void *p2, int j, int i, int k, int l);

int func_020b076c(void *p1, void *p2, int p3)
{
    unsigned char *ptr;
    UnkStruct_020b076c *s;
    int start;
    void *r;
    int i, j, k, l;

    s = func_0204e414();
    start = 1;
    for (i = 1; i <= 4; i++) {
        for (j = start; j <= 4; j++) {
            if (j < s->width && i < s->height && s->base) {
                ptr = s->base + (i * s->width + j) * 0x28;
            } else {
                ptr = 0;
            }
            if (ptr) {
                for (k = 0; k < 16; k++) {
                    for (l = 0; l < 16; l++) {
                        r = func_02037e0c(ptr, l, k, 0);
                        if (r && func_0204bb54(r) && p3 == func_0204bb2c(r)) {
                            func_0204f800(p1, p2, j, i, l, k);
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
