/* func_0205685c @ 0x0205685c, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0205685c {
    char pad_00[0x18];
    int unk_18;
    void *unk_1C;
    char pad_20[0x26 - 0x20];
    unsigned char unk_26;
    char pad_27[0x28 - 0x27];
    void *unk_28;
};

extern void *data_021fbe94;
extern void *func_021077e8(int);
extern void *func_020e9948(void *, int);
extern void *func_02056a8c(void *);
extern int func_02056a4c(void *);

int func_0205685c(struct UnkStruct_0205685c *s, int a, int b, unsigned char c, void *heap)
{
    int i;

    s->unk_18 = a;
    if (!heap) {
        heap = data_021fbe94;
    }
    s->unk_1C = func_021077e8(b);
    s->unk_26 = c;
    s->unk_28 = func_020e9948(heap, 40 * s->unk_26);
    if (!s->unk_28) {
        return 0;
    }
    for (i = 0; i < s->unk_26; i++) {
        if ((char *) s->unk_28 + 40 * i) {
            func_02056a8c((char *) s->unk_28 + 40 * i);
        }
        if (!func_02056a4c((char *) s->unk_28 + 40 * i)) {
            return 0;
        }
    }
    return 1;
}
