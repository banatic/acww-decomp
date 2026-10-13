/* func_02040548 @ 0x02040548, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char unk_03;
} UnkStruct_02040548;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_02040548_2;

extern char data_021dc7a8[];

extern void *func_0207cec0(void *tbl, int idx);
extern int func_0207b3dc(void *tbl);
extern int func_020405a8(void *h, int a);
extern unsigned char *func_02080a2c(void *h);

void func_02040548(UnkStruct_02040548_2 *p, UnkStruct_02040548 *out, int idx)
{
    char *base;
    void *h;
    unsigned char *e;

    base = (char *) data_021dc7a8;
    *(int *) out = 0;
    if (idx < 0 || idx > 7) {
        idx -= 0x4b;
    }
    h = func_0207cec0(base + 0x9284, idx);
    if (func_020405a8(h, func_0207b3dc(base + 0x9284))) {
        e = func_02080a2c(h);
        if (e) {
            out->unk_03 = e[0];
            out->unk_02 = e[1];
            out->unk_01 = (unsigned char) p->unk_08;
        }
    }
}
