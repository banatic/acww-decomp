/* func_02048fdc @ 0x02048fdc, 0x5e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y;
} Pair;
typedef struct {
    int pad_00;
    Pair sub;
} UnkStruct_02048fdc;
typedef struct {
    int pad_00;
} UnkStruct_02048fdc_2;
extern void func_020496f8(UnkStruct_02048fdc_2 *, UnkStruct_02048fdc *, Pair *);
extern void func_02049638(UnkStruct_02048fdc_2 *, UnkStruct_02048fdc *, Pair *);
extern void func_020493d4(UnkStruct_02048fdc_2 *, UnkStruct_02048fdc *, Pair *);
extern void func_02049160(UnkStruct_02048fdc_2 *, UnkStruct_02048fdc *, int, int);
extern void func_0204903c(UnkStruct_02048fdc_2 *, UnkStruct_02048fdc *, Pair *);

void func_02048fdc(UnkStruct_02048fdc_2 *a0, UnkStruct_02048fdc *a1, int a2, int a3)
{
    Pair *s;
    Pair t1, t2, t3, t4;
    int hi, lo;

    s = &a1->sub;
    hi = s->y << 4;
    lo = s->x << 4;
    t1.x = lo;
    t1.y = hi;
    func_020496f8(a0, a1, &t1);
    t2.x = lo;
    t2.y = hi;
    func_02049638(a0, a1, &t2);
    t3.x = lo;
    t3.y = hi;
    func_020493d4(a0, a1, &t3);
    func_02049160(a0, a1, a2, a3);
    t4.x = lo;
    t4.y = hi;
    func_0204903c(a0, a1, &t4);
}
