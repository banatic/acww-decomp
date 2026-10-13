/* func_0201b268 @ 0x0201b268, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e88dc(int *a, int b, int c);
extern int func_0200322c(void *a, void *b);
extern int func_020ea990(void *a, void *b);
extern void func_02003244(void *a, void *b);
typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    char pad0[0x44 - 0x0c];
    char unk_44;
} UnkStruct_0201b268;
typedef struct {
    char pad0[0x5c];
    char unk_5C;
    char pad_5D[0x94 - 0x5d];
    short unk_94;
    char pad_96[0x98 - 0x96];
    int unk_98;
    char pad_9C[0x4cc - 0x9c];
    char unk_4CC;
} UnkStruct_0201b268_2;
void func_0201b268(UnkStruct_0201b268 *p, UnkStruct_0201b268_2 *q)
{
    if (p->unk_00 == 0) {
        q->unk_98 = 0;
    } else {
        int r2 = (p->unk_04 < p->unk_00) ? (p->unk_04) : (p->unk_08);
        func_020e88dc(&q->unk_98, p->unk_00, r2);
        r2 = func_0200322c(&q->unk_5C, &p->unk_44);
        if (r2 == q->unk_94) {
            int tmp = func_020ea990(&p->unk_44, &q->unk_5C);
            if (tmp < q->unk_98) {
                q->unk_98 = tmp;
            }
        }
    }
    func_02003244(q, &q->unk_4CC);
}
