/* func_ov095_0229b400 @ 0x0229b400, 0x52 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov095_0229b3ec(void *s, int a, int b);

typedef struct {
    unsigned short arr[6];
    int count;
} UnkStruct_0229b400;

void func_ov095_0229b400(UnkStruct_0229b400 *s, int val, int mode)
{
    switch (mode) {
        case 0:
            func_ov095_0229b3ec(s, val, mode);
            s->arr[s->count] = val;
            break;
        case 1:
            s->arr[s->count] = val;
            break;
        case 2: {
            unsigned short last;
            if (s->count > 0) {
                last = s->arr[s->count - 1];
                func_ov095_0229b3ec(s, (s->count - 1) * 2, mode);
            }
            s->arr[0] = last;
            s->arr[1] = val;
            s->count = 2;
            return;
        }
        default:
            break;
    }
    if (s->count < 6) {
        s->count++;
    }
}
