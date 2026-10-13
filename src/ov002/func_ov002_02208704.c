/* func_ov002_02208704 @ 0x02208704, 0x60 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xc];
    int unk_0C;
    int unk_10;
    int unk_14;
} UnkStruct_02208704;

extern int func_ov002_022087f4(UnkStruct_02208704 *p, int v);
extern void func_ov002_02208348(UnkStruct_02208704 *p, int v);
extern void func_02001b6c(int v);
extern void func_02001d00(int v);
extern void func_02001ba4(int v);
extern void func_02001d1c(int v);

void func_ov002_02208704(UnkStruct_02208704 *p, int dir)
{
    p->unk_0C = func_ov002_022087f4(p, p->unk_10);
    switch (dir) {
        case 0:
            if (p->unk_0C > p->unk_14) {
                func_ov002_02208348(p, 2);
            } else {
                func_02001b6c(1);
                func_02001d00(0x1f);
            }
            break;
        case 1:
            if (p->unk_0C > p->unk_14) {
                func_ov002_02208348(p, 0);
            } else {
                func_02001ba4(1);
                func_02001d1c(0x1f);
            }
            break;
    }
}
