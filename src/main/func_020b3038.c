/* func_020b3038 @ 0x020b3038, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020b3038 {
    void *data;
    int x_limit;
    int y_limit;
} UnkStruct_020b3038;

extern UnkStruct_020b3038 *func_0204e414(void);
extern int func_0204f658(UnkStruct_020b3038 *s, int x, int y);
extern void func_0204f800(int *out0, int *out1, int x, int y, int w, int h);
extern int func_02037e0c(void *ptr, int a, int b, int c);
int func_020b3038(int *out0, int *out1)
{
    int x, y;
    UnkStruct_020b3038 *s = func_0204e414();
    int x_limit, y_limit;
    int found = 0;
    void *ptr;

    *out0 = 0;
    *out1 = 0;
    if (s == 0) {
        goto fail;
    }

    x_limit = s->x_limit;
    y_limit = s->y_limit;

    y = 0;
    for (; y < y_limit; y++) {
        for (x = 0; x < x_limit; x++) {
            if (func_0204f658(s, x, y) & 0x200) {
                found = 1;
                break;
            }
        }
        if (found) {
            break;
        }
    }

    if (found == 0) {
        goto fail;
    }

    func_0204f800(out0, out1, x, y, 10, 9);

    if ((unsigned) x < (unsigned) s->x_limit && (unsigned) y < (unsigned) s->y_limit && s->data != 0) {
        ptr = (char *) s->data + (x + y * s->x_limit) * 40;
    } else {
        ptr = 0;
    }
    if (ptr == 0) {
        goto fail;
    }

    return func_02037e0c(ptr, 10, 9, 0);
fail:
    return 0;
}
