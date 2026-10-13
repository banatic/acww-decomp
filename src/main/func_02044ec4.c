/* func_02044ec4 @ 0x02044ec4, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_loop_invariants off

extern void func_0204a2a4(void *p, int a, int b, int c, int d);

typedef struct {
    unsigned char flag : 1;
    unsigned char : 2;
    unsigned char field5 : 5;
    unsigned char : 3;
    unsigned char field2 : 2;
    unsigned char : 3;
    unsigned short unk_02;
    unsigned short unk_04;
    unsigned short arr[3];
    unsigned short unk_0C;
} UnkStruct_02044ec4;

void func_02044ec4(UnkStruct_02044ec4 *s, void *p)
{
    int v = s->field5;
    switch (v) {
        case 12:
        case 13:
        case 15:
        case 23:
            return;
        default:
            break;
    }
    func_0204a2a4(p, s->unk_02 >> 8, s->unk_02 & 0xff, s->unk_04, s->field2);
    if (s->flag) {
        unsigned short h12 = s->unk_0C;
        int zero = 0;
        int i = 0;
        for (; i < 3; i++) {
            unsigned short *w = (unsigned short *) ((int) s + 6);
            func_0204a2a4(p, w[i] >> 8, w[i] & 0xff, h12, zero);
        }
    }
}
