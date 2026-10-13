/* func_ov109_0229c934 @ 0x0229c934, 0x54 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x218c];
    unsigned char unk_218C[1];
    char pad_218D[0x844];
    unsigned char unk_29D1;
    unsigned char unk_29D2;
    unsigned char unk_29D3;
} UnkStruct_0229c934;

extern int func_ov109_0229ccb4(UnkStruct_0229c934 *s, unsigned char b);
extern int func_ov109_0229cab0(UnkStruct_0229c934 *s, unsigned char b);
extern void func_ov002_02207cf0(unsigned char *p);
extern void func_ov002_02207cf8(unsigned char *p);

void func_ov109_0229c934(UnkStruct_0229c934 *s)
{
    if (func_ov109_0229ccb4(s, s->unk_29D3)) {
        if (func_ov109_0229cab0(s, s->unk_29D3)) {
            func_ov002_02207cf0(s->unk_218C);
        } else {
            s->unk_29D1 = s->unk_29D3;
            func_ov002_02207cf8(s->unk_218C);
        }
    } else {
        func_ov002_02207cf0(s->unk_218C);
    }
}
