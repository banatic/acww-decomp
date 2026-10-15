/* func_ov114_0229d244 @ 0x0229d244, 0x94 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O1,s
 */

extern unsigned short data_021fbe40;
extern void func_ov002_0220a4c8(void);
extern void func_ov114_0229d4c0(void *);

void func_ov114_0229d244(void *self)
{
    int original;
    unsigned char sw;
    unsigned short keys;

    original = *(int *) ((char *) self + 0x1270);
    sw = *(unsigned char *) ((char *) self + 0x12bb);

    switch (sw) {
        case 2:
            keys = data_021fbe40;
            if (keys & 0x20) {
                *(int *) ((char *) self + 0x1270) = original - 2;
            } else if (keys & 0x10) {
                *(int *) ((char *) self + 0x1270) = original + 2;
            }
            break;
        case 0:
            *(int *) ((char *) self + 0x1270) = original - 2;
            break;
        case 1:
            *(int *) ((char *) self + 0x1270) = original + 2;
            break;
        default:
            break;
    }

    if (*(int *) ((char *) self + 0x1270) < 0) {
        *(int *) ((char *) self + 0x1270) = 0;
    }
    if (*(int *) ((char *) self + 0x1270) > 0x8c) {
        *(int *) ((char *) self + 0x1270) = 0x8c;
    }

    if (*(int *) ((char *) self + 0x1270) != original) {
        asm {
            ldr r0, =0x121c
            add r0, self, r0
        }
        func_ov002_0220a4c8();
    }

    func_ov114_0229d4c0(self);
}
