/* func_ov003_0220d914 @ 0x0220d914, 0xa4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char *func_0205e8e4(void *);
extern int func_02056f94(void *);
extern void *func_020984fc(void *);
extern void func_0209971c(void *, void *);
extern void func_0205eb8c(void *, void *, int);
extern int func_02008258(void *, int);
extern void func_0200d4e8(void *, int, int, int);

struct UnkStruct_0220d914 {
    char pad_00[0x5a0];
    char unk_5A0[1];
    char pad_5A1[0x7d4 - 0x5a1];
    unsigned char unk_7D4[0x1c];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
    void *unk_800;
};

void func_ov003_0220d914(struct UnkStruct_0220d914 *o)
{
    unsigned short h[2];
    unsigned char *q;
    unsigned char *p;
    void *w;
    if (func_02056f94(func_0205e8e4(o->unk_5A0) + 0x9c) != 0) {
        q = o->unk_7D4;
        p = &q[4];
        if (*p != 0) {
            *p = *p - 1;
        }
        if (*p == 0) {
            p = &q[5];
            if (*p != 0) {
                *p = *p - 1;
            }
            if (*p == 0) {
                w = func_020984fc(o->unk_800);
                h[0] = 0xfff1;
                func_0209971c(w, h);
                h[1] = 0xfff1;
                func_0205eb8c(o->unk_5A0, &h[1], 0);
                o->unk_7FC = func_02008258(o, o->unk_7F0);
                func_0200d4e8(o, 9, 1, -1);
            }
        }
    }
}
