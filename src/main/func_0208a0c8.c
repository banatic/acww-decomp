/* func_0208a0c8 @ 0x0208a0c8, 0x7a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} Frame;
typedef struct {
    Frame *frames;
    int count;
} Res;
typedef struct {
    Res *res;
    int idx;
    int acc;
    int step;
    int flag;
} UnkStruct_0208a0c8;

void func_0208a0c8(UnkStruct_0208a0c8 *s)
{
    int n;

    if (s->flag == 0) {
        s->acc = s->acc + s->step;
        if ((s->acc >> 12) >= s->res->frames[s->idx].unk_04) {
            s->acc = 0;
            n = s->res->count;
            s->idx = s->idx + 1;
            if (s->idx >= n) {
                s->idx = 0;
            }
        }
    } else {
        s->acc = s->acc + s->step;
        if ((s->acc >> 12) >= s->res->frames[s->idx].unk_04) {
            n = s->res->count;
            s->idx = s->idx + 1;
            if (s->idx < n) {
                s->acc = 0;
            } else {
                s->idx = n - 1;
            }
        }
    }
}
