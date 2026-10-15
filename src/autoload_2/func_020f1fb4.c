/* func_020f1fb4 @ 0x020f1fb4, 0x384 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int func_020eedb8(int seq, int a, void *h);
extern int func_020eede8(int seq, int a);
extern void func_020f12cc(void *p, int a);

typedef struct {
    unsigned char pad_00[0x38];
    void *unk_38;
    unsigned char pad_3C[4];
    void *unk_40;
    unsigned char pad_44[0x4d - 0x44];
    unsigned char unk_4D;
    unsigned char pad_4E[0x72 - 0x4e];
    unsigned char unk_72;
} UnkStruct_020f1fb4;

void func_020f1fb4(UnkStruct_020f1fb4 *p, int seq)
{
    if (p->unk_4D != 0) {
        return;
    }

    switch (seq) {
        case 3:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 21:
        case 25:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
        case 0x85f:
        case 0x865:
        case 0x866:
        case 0x867:
        case 0x868:
        case 0x869:
        case 0x86a:
        case 0x86b:
        case 0x86c:
        case 0x86d:
        case 0x86e:
        case 0x87f:
        case 0x880:
        case 0x881:
        case 0x882:
            func_020eedb8((unsigned short) (seq % 1000), (unsigned short) (seq / 1000), &p->unk_38);
            func_020f12cc(p, 0);
            break;
        case 0x861:
            func_020eedb8((unsigned short) (seq % 1000), (unsigned short) (seq / 1000), &p->unk_40);
            func_020f12cc(p, 0);
            break;
        case 1:
        case 2:
            p->unk_72 = 0xf;
            func_020eede8((unsigned short) (seq % 1000), (unsigned short) (seq / 1000));
            break;
        default:
            func_020eede8((unsigned short) (seq % 1000), (unsigned short) (seq / 1000));
            break;
    }
}
