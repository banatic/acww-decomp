/* func_ov112_0229f35c @ 0x0229f35c, 0x84 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov112_0229fe70(void *p, int a);
extern int func_ov095_02299b7c(void *p);
extern int func_ov095_02299b38(void *p);
extern void func_ov002_0220a000(void *p, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);

typedef struct {
    char pad_00[0x98];
    int unk_98;
    int unk_9C;
    char pad_A0[0xb7 - 0xa0];
    unsigned char unk_B7;
    char pad_B8[0xc1 - 0xb8];
    unsigned char unk_C1;
} UnkStruct_0229f35c;

void func_ov112_0229f35c(UnkStruct_0229f35c *p)
{
    if (func_ov112_0229fe70(p, 0x800) != 0) {
        func_ov002_0220a000((char *) p + 0x4448, p->unk_98, p->unk_9C - p->unk_B7, 3, 2);
        p->unk_C1 = 0xc;
    } else {
        int a = func_ov095_02299b7c((char *) p + 0x384);
        int b = func_ov095_02299b38((char *) p + 0x384);
        func_ov002_0220a000((char *) p + 0x4448, a, b, 3, 2);
        p->unk_C1 = 0x6;
    }
    func_ov002_02208098(p, 7);
}
