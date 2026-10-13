/* func_020aebcc @ 0x020aebcc, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int pad_00;
    unsigned short arr[43];
    union {
        unsigned short raw;
        struct {
            unsigned short f0 : 5;
            unsigned short counter : 4;
            unsigned short f1 : 7;
        } bits;
    } unk_5A;
} UnkStruct_020aebcc;

extern unsigned int func_020aef44(UnkStruct_020aebcc *s);

void func_020aebcc(UnkStruct_020aebcc *s, int *counter)
{
    unsigned int i = 0;
    while (i < func_020aef44(s)) {
        unsigned int v = s->unk_5A.bits.counter & 0xF;
        unsigned short out;
        if (v < 16) {
            out = (unsigned short) (0x1521 + v);
        } else {
            out = 0x1521;
        }
        s->arr[(*counter)++] = out;
        s->unk_5A.raw =
            (unsigned short) ((s->unk_5A.raw & ~0x1E0) | (((unsigned short) (s->unk_5A.bits.counter + 1) & 0xF) << 5));
        i++;
    }
}
