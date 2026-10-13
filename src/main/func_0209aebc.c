/* func_0209aebc @ 0x0209aebc, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209bd44(void *);
extern int func_02003704(void *);
extern int memcmp(void *, void *, int);

int func_0209aebc(void *r0, void *r1)
{
    int result;
    void *p = r0;
    void *q = r1;

    if (func_0209bd44((char *) p + 0x10) != 0) {
        if (func_02003704(q) != 0) {
            if (*(unsigned short *) q == *(unsigned short *) p) {
                if (memcmp((char *) q + 2, (char *) p + 2, 0xc) == 0) {
                    if (*(unsigned char *) ((char *) q + 0xf) == *(unsigned char *) ((char *) p + 0xf)) {
                        result = 1;
                        goto done;
                    }
                }
            }
        }
    }
    result = 0;
done:
    return result;
}
