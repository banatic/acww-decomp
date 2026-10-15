/* func_0200bb60 @ 0x0200bb60, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void *);
extern int func_0200b83c(void *, unsigned int *, int, int, int, int);

typedef struct {
    int unk_00;
    unsigned char unk_04;
    unsigned char unk_05;
    unsigned char unk_06;
} UnkStruct_0200bb60;

void func_0200bb60(void *p)
{
    UnkStruct_0200bb60 *s = (UnkStruct_0200bb60 *) ((char *) p + 0x7d4);
    int w0 = s->unk_00;
    unsigned char b5 = s->unk_05;
    unsigned char b6 = s->unk_06;
    unsigned char b4 = s->unk_04;

    if (b4 >= 3) {
        func_02010f5c(p);
        return;
    }

    if (w0 >= 0) {
        unsigned int local[2];
        local[0] = b5;
        local[1] = b6;
        func_0200b83c(p, local, w0, 0, 6, -1);
    } else {
        if (b4 == 0) {
            int g = *(int *) ((char *) p + 0x818);
            if (g == 2) {
                s->unk_04 = 2;
            } else if (g == 1) {
                s->unk_04 = 1;
            }
        }
    }

    func_02010f5c(p);
}
