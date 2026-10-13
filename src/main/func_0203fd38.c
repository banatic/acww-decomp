/* func_0203fd38 @ 0x0203fd38, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef union {
    unsigned int w[2];
    struct {
        unsigned short f0;
        unsigned char f2, f3, f4, f5, f6, f7;
    } unk_00;
} Stamp;

typedef struct {
    unsigned char pad_00[4];
    int f4;
    unsigned char pad_08[9 - 8];
    unsigned char unk_09;
    unsigned char unk_0A;
    unsigned char unk_0B;
} Target;

typedef union {
    unsigned int word;
    unsigned char bytes[4];
} Packed;

typedef struct {
    Packed packed;
    Stamp s2;
} Combined;

extern void *func_0203fda0(void *self, Stamp *param2);
extern int func_0209e350(Stamp *a, Stamp *b);

int func_0203fd38(void *self, Stamp *param1, Stamp *param2)
{
    int result;
    Target *target;

    result = 0;
    target = (Target *) func_0203fda0(self, param2);
    if (target != 0) {
        Combined c;
        c.packed.word = 0;
        c.packed.bytes[3] = param1->unk_00.f4;
        c.packed.bytes[2] = param1->unk_00.f3;
        c.packed.bytes[1] = param1->unk_00.f2;
        if ((unsigned int) target->f4 <= c.packed.word) {
            int cmp;

            c.s2.w[0] = 0;
            c.s2.w[1] = 0;
            c.s2.w[0] = 0;
            c.s2.w[1] = 0;
            c.s2.unk_00.f5 = param1->unk_00.f5;
            c.s2.unk_00.f4 = target->unk_0B;
            c.s2.unk_00.f3 = target->unk_0A;
            c.s2.unk_00.f2 = target->unk_09;

            cmp = func_0209e350(param1, &c.s2);
            if (cmp > 0) {
                if (cmp <= 5) {
                    result = 3;
                } else {
                    result = 2;
                }
            }
        } else {
            result = 1;
        }
    }
    return result;
}
