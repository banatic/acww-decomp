/* func_ov003_02223a90 @ 0x02223a90, 0x88 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02222bc0(void *);
extern void func_ov003_02223580(void *);

void func_ov003_02223a90(void *p)
{
    int i, j, off;
    char *base;

    func_ov003_02222bc0((char *) p + 0x1e4c);

    for (i = 0; i < 5; i++) {
        *((int *) ((char *) p + i * 0x18 + 0x1dd4)) = 0;
    }

    for (i = 0; i < 3; i++) {
        j = 0;
        base = (char *) p + i * 0x530;
        do {
            func_ov003_02223580(base + j * 0x14c);
            j++;
        } while (j < 4);
    }

    for (i = 0; i < 4; i++) {
        off = i * 0x14c;
        func_ov003_02223580((char *) p + 0xf90 + off);
        func_ov003_02223580((char *) p + 0x18a4 + off);
    }
}
