/* func_02048298 @ 0x02048298, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x18];
    unsigned short n;
} UnkStruct_02048298;

extern unsigned char data_021c7a08[];
extern int func_020644cc(int p5);
extern int func_0204830c(void *p0, void *p1, UnkStruct_02048298 *e, int p4, int j, int i);

int func_02048298(void *p0, void *p1, int nx, int ny, int p4, int p5)
{
    int j, i;
    int rem;
    UnkStruct_02048298 *e;

    rem = func_020644cc(p5);
    for (i = 0; i < ny; i++) {
        for (j = 0; j < nx; j++) {
            e = (UnkStruct_02048298 *) (data_021c7a08 + j * 0x90 + i * 0x24);

            if ((int) e->n > 0) {
                rem -= e->n;
                if (rem < 0) {
                    if (func_0204830c(p0, p1, e, p4, j, i) != 0) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
