/* func_020b0594 @ 0x020b0594, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b0a20(void *p);
extern int func_020b0918(void *p);
extern int func_020b08c0(void *p);
extern int func_020b08b8(void *p);

typedef struct {
    unsigned short a : 7;
    unsigned short b : 4;
    unsigned short c : 5;
} Packed;

int func_020b0594(char *base, unsigned int index, int *out1, int *out2, int *out3, unsigned char *out4, unsigned char *out5,
                  unsigned char *out6)
{
    char *p;

    if (index < 3) {
        p = base + index * 6;
        if (func_020b0a20(p) != 0) {
            if (out1 != 0) {
                *out1 = func_020b0918(p);
            }
            if (out2 != 0) {
                *out2 = func_020b08c0(p);
            }
            if (out3 != 0) {
                *out3 = func_020b08b8(p);
            }
            if (out4 != 0) {
                *out4 = ((Packed *) p)->a;
            }
            if (out5 != 0) {
                *out5 = ((Packed *) (base + index * 6))->b;
            }
            if (out6 != 0) {
                *out6 = ((Packed *) (base + index * 6))->c;
            }
            return 1;
        }
    }
    return 0;
}
