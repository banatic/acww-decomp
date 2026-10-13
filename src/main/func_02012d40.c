/* func_02012d40 @ 0x02012d40, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
} Pair;
typedef struct {
    int pad_00[3];
    Pair sub;
} UnkStruct_02012d40;
typedef struct {
    int pad_00;
    int unk_04;
} UnkStruct_02012d40_2;
extern UnkStruct_02012d40 *data_021c80bc;
extern void func_02012d84(UnkStruct_02012d40_2 *, void *, Pair *, UnkStruct_02012d40 *);
extern int func_02013518(UnkStruct_02012d40_2 *, void *);

int func_02012d40(UnkStruct_02012d40_2 *a, void *b)
{
    UnkStruct_02012d40 *g;
    Pair *s;
    Pair tmp;

    g = data_021c80bc;
    if (g == 0) {
        goto fail;
    }
    s = &g->sub;
    tmp.x = s->x;
    tmp.y = s->y;
    func_02012d84(a, b, &tmp, g);
    if (func_02013518(a, b) == 0) {
        goto fail;
    }
    a->unk_04 = 2;
    return 1;
fail:
    return 0;
}
