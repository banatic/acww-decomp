/* func_ov124_0229f0ec @ 0x0229f0ec, 0x190 bytes, Thumb, module ov124
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xe8];
    unsigned char unk_E8;
} UnkStruct_0229f0ec;

extern void *data_021fbe94;
extern const unsigned char data_ov124_0229f628[];
extern const unsigned char data_ov124_0229f638[];
extern const unsigned char data_ov124_0229f648[];
extern const unsigned char data_ov124_0229f65c[];
extern void *data_ov124_0229f578[];

extern int func_02002c6c(const void *a, void *b, void *c, int d, int e, int f);
extern int func_02002d14(const void *a, void *b, void *c, int d, int e, int f);
extern int func_02002cd8(const void *a, void *b, void *c, int d, int e);
extern int func_02002ca4(void *a, void *b, void *c);
extern int func_02064328(void *dst, const void *src, int n);
extern int func_0206fca4(void);

int func_ov124_0229f0ec(UnkStruct_0229f0ec *o, void *p1, int p2)
{
    void *heap;
    char buf[0x24];

    heap = data_021fbe94;
    func_02002c6c(data_ov124_0229f628, heap, p1, 0x10, 0x10, 0x169);
    func_02002d14(data_ov124_0229f638, heap, p1, 1, 1, 6);
    switch (func_0206fca4()) {
        case 4:
        case 5:
        case 7:
        case 8:
            o->unk_E8 = 0;
            break;
        case 6:
        case 9:
            o->unk_E8 = 2;
            break;
        case 0xb:
            o->unk_E8 = 1;
            break;
        case 0xc:
            o->unk_E8 = 3;
            break;
        case 0xd:
            o->unk_E8 = 4;
            break;
        case 0xe:
            o->unk_E8 = 7;
            break;
        case 0xf:
        case 0x1a:
        case 0x1b:
            o->unk_E8 = 5;
            break;
        case 0x10:
        case 0x18:
        case 0x19:
            o->unk_E8 = 6;
            break;
        case 0x11:
            o->unk_E8 = 8;
            break;
        case 0x12:
            o->unk_E8 = 0xe;
            break;
        case 0x13:
            o->unk_E8 = 0xd;
            break;
        case 0x14:
            o->unk_E8 = 0xc;
            break;
        case 0x15:
            o->unk_E8 = 0xb;
            break;
        case 0x16:
            o->unk_E8 = 9;
            break;
        case 0x17:
            o->unk_E8 = 0xa;
            break;
        case 0xa:
            o->unk_E8 = 0xf;
            break;
        default:
            o->unk_E8 = 0;
            break;
    }
    func_02064328(buf, data_ov124_0229f648, o->unk_E8);
    func_02002c6c(buf, heap, p1, 0x113, 0x113, 0x126);
    func_02002cd8(data_ov124_0229f65c, heap, p1, o->unk_E8, 0xe);
    return func_02002ca4(data_ov124_0229f578[p2], heap, p1);
}
