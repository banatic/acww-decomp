/* func_ov112_0229f92c @ 0x0229f92c, 0x58 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a4c8(void);
extern void func_ov112_0229fb8c(void *, int);

extern volatile unsigned short data_021fbe40;

void func_ov112_0229f92c(void *p)
{
    int adj;
    unsigned char *base = (unsigned char *) p;
    unsigned char v;
    unsigned short reg;

    v = base[0xb6];
    adj = v;
    reg = data_021fbe40;

    if (reg & 0x40) {
        adj = v - 4;
    } else if (reg & 0x80) {
        adj = v + 4;
    }

    if (adj < 0) {
        adj = 0;
    }
    if (adj > 60) {
        adj = 60;
    }

    if (v != adj) {
        asm {
            ldr r0, =0x4234
            add r0, base, r0
        }
        func_ov002_0220a4c8();
    }

    func_ov112_0229fb8c(base, adj);
}
