/* func_0207cc94 @ 0x0207cc94, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cee4(void *self, int i);
extern int func_0207cf14(void *self, void *item);
extern int func_0207cf74(int idx);
extern int func_02003704(void *p);
extern int func_020644cc(int v);
extern void MI_CpuFill8(void *, int, unsigned int);

void *func_0207cc94(void *self, void **list, int n)
{
    int count = 0;
    int idx;
    int zero;
    int i;
    void *result = 0;
    unsigned char buf[8];

    MI_CpuFill8(buf, 0, 8);

    i = 0;
    do {
        if (func_0207cee4(self, i)) {
            buf[i] = 1;
            count++;
        }
        i++;
    } while (i < 8);

    zero = 0;
    for (i = 0; i < n; i++) {
        if (list[i]) {
            idx = func_0207cf14(self, list[i]);
            if (func_0207cf74(idx)) {
                buf[idx] = zero;
                if (func_02003704(list[i])) {
                    count--;
                }
            }
        }
    }

    if (count > 0) {
        int r = func_020644cc(count);
        for (i = 0; i < 8; i++) {
            if (buf[i] == 1) {
                if (r == 0) {
                    result = (char *) self + i * 0x7ec;
                    break;
                }
                r--;
            }
        }
    }

    return result;
}