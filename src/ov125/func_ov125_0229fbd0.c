/* func_ov125_0229fbd0 @ 0x0229fbd0, 0x54 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206fc80(int);
extern void func_0206fc4c(int);
extern void func_ov002_02207d24(void *, int);
extern void func_ov002_022080a0(void *, int);
extern void func_ov125_0229fe98(void *);

typedef struct {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
    unsigned char pad_8D[0x7ee];
    unsigned char unk_87B;
    unsigned char unk_87C;
    unsigned char unk_87D;
} UnkStruct_0229fbd0;

void func_ov125_0229fbd0(UnkStruct_0229fbd0 *p)
{
    switch (p->unk_87D) {
        case 0:
            func_0206fc80(p->unk_87B);
            func_0206fc4c(1);
            p->unk_8C = 3;
            func_ov002_02207d24((char *) p + 0x574, 1);
            func_ov002_022080a0(p, 1);
            break;
        case 1:
        default:
            func_ov125_0229fe98(p);
            break;
    }
}
