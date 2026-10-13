/* func_0204763c @ 0x0204763c, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int pad_00;
    int unk_04;
    int unk_08;
} FieldStruct;

typedef struct {
    int x;
    int y;
} UnkStruct_0204763c;

extern int data_021c79c4;

FieldStruct *func_0204e414(void *a, int b);
void func_0209e474(UnkStruct_0204763c *l);
void func_0204a3cc(int *g, FieldStruct *b);
void func_02047688(void *a, FieldStruct *b, int c, int d, UnkStruct_0204763c *e, int f);

void func_0204763c(void *a, int b)
{
    UnkStruct_0204763c local;
    FieldStruct *p;
    int c, d;

    p = func_0204e414(a, b);
    if (p == 0) {
        return;
    }

    local.x = 0;
    local.y = 0;
    func_0209e474(&local);
    c = p->unk_04 - 2;
    d = p->unk_08 - 2;
    func_0204a3cc(&data_021c79c4, p);
    func_02047688(a, p, c, d, &local, b);
}
