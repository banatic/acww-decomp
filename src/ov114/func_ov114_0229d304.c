/* func_ov114_0229d304 @ 0x0229d304, 0x28 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x121c];
    char unk_121C;
    char pad_121D[158];
    unsigned char flag;
} UnkStruct_0229d304;

extern void func_ov002_0220a568(void *);

void func_ov114_0229d304(UnkStruct_0229d304 *p)
{
    if (p->flag == 2) {
        func_ov002_0220a568(&p->unk_121C);
    }
    p->flag = 4;
}
