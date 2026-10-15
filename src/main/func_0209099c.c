/* func_0209099c @ 0x0209099c, 0x5a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02090a2c(void *);

typedef struct {
    int unk_00;
    int pad_04;
    unsigned char unk_08;
    char pad_09[7];
    int (*fnarr[2])(void *);
} UnkStruct_0209099c;

typedef struct {
    char unk_00;
    char pad_01[3];
    UnkStruct_0209099c elems[32];
} UnkStruct_0209099c_2;

void func_0209099c(UnkStruct_0209099c_2 *out)
{
    UnkStruct_0209099c *p = out->elems;
    int i = 0;
    int val = i;
    int c = i;
    int sentinel = i;
    unsigned int t;
    int (**fp)(void *);

    for (; i < 32; p++, i++) {
        if (p->unk_00 != ~sentinel) {
            fp = p->fnarr;
            p->unk_08 = (char) val;
            if (fp != 0) {
                if (fp[1](p) != 0) {
                    p->unk_08 = 1;
                }
            }
            if (p->unk_08 == 1) {
                t = 1;
            } else {
                t = c;
            }
            if (t == 0) {
                func_02090a2c(p);
                out->unk_00 = (char) i;
            }
        }
    }
}
