/* func_020a94a4 @ 0x020a94a4, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a9c9c(void *p);
extern void func_020a9ccc(void *p);

typedef struct {
    int pad_00;
    int unk_04;
    void *unk_08;
} UnkStruct_020a94a4;

void func_020a94a4(UnkStruct_020a94a4 *s)
{
    s->unk_04 = 0;
    while (func_020a9c9c((void *) &s->unk_08) == 0) {
        func_020a9ccc((void *) &s->unk_08);
    }
}
