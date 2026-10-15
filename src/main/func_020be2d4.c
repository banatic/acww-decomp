/* func_020be2d4 @ 0x020be2d4, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char pad_0A[2];
} UnkStruct_020be2d4;

typedef struct {
    char pad_00[0x1b30];
    UnkStruct_020be2d4 arr[5];
    char sub[0x134c];
    char other;
} UnkStruct_020be2d4_2;

extern int func_020bec70(void *a, int v);
extern void func_020bee9c(UnkStruct_020be2d4 *e, void *b);
extern void func_020bed64(void *a, void *b, int v);

void func_020be2d4(UnkStruct_020be2d4_2 *self, void *arg)
{
    UnkStruct_020be2d4 *end;
    UnkStruct_020be2d4 *e;
    int v;
    int r;
    int flag;

    end = &self->arr[5];
    e = self->arr;
    while (e < end) {
        v = e->unk_00;
        if (e->unk_09 != 0) {
            if (v != 0x34) {
                flag = e->unk_08;
                r = func_020bec70(&self->other, v);
                if (flag == 0) {
                    func_020bee9c(e, self->sub);
                    e->unk_08 = 1;
                }
                if (r == 0) {
                    func_020bed64(&self->other, self->sub, v);
                }
            }
            e->unk_09 = 0;
        }
        e++;
    }
}
