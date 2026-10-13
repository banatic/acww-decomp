/* func_ov003_02222b78 @ 0x02222b78, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e993c(void *, void *);
extern void *data_ov003_0223cf78;

typedef struct {
    void *a[8][4];
} UnkStruct_02222b78;

void func_ov003_02222b78(UnkStruct_02222b78 *s)
{
    void *ctx = data_ov003_0223cf78;
    int i = 0;
    int j = 0;
    void *nul = 0;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 4; j++) {
            if (s->a[i][j] != 0) {
                func_020e993c(ctx, s->a[i][j]);
                s->a[i][j] = nul;
            }
        }
    }
}
