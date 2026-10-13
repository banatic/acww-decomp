/* func_0209a854 @ 0x0209a854, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02003704(void *);
extern int func_0209ac04(void *);
extern int memcmp(void *, void *, int);

int func_0209a854(void *r0, void *r1)
{
    int r5 = (int) r0;
    int r4 = (int) r1;
    if (func_02003704((void *) r4) != 0) {
        if (func_0209ac04((void *) r5) != 0) {
            if (*(unsigned short *) r4 == *(unsigned short *) (r5 + 0x70)) {
                if (memcmp((void *) (r4 + 2), (void *) (r5 + 0x72), 0xc) == 0) {
                    if (*(unsigned char *) (r4 + 0xf) == *(unsigned char *) (r5 + 0x7f)) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
