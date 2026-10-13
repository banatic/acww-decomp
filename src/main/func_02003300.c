/* func_02003300 @ 0x02003300, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void VEC_Add(void *a, void *b, void *c);

void func_02003300(void *param0, void *param1)
{
    void *sp;
    unsigned int *r5;
    unsigned int *r4;
    unsigned int *r0;
    unsigned int *r1;
    unsigned int *r2;

    r5 = param0;
    r4 = param1;
    r0 = (unsigned int *) ((char *) r5 + 0x5c);
    r1 = (unsigned int *) ((char *) r5 + 0xa4);
    r2 = r0;
    VEC_Add(r0, r1, r2);
    if (r4 != 0) {
        r1 = (unsigned int *) ((char *) r5 + 0x5c);
        r0 = (unsigned int *) ((char *) r4 + 0x10);
        *r1 = *r1 + *r0;
        r1 = (unsigned int *) ((char *) r5 + 0x64);
        r0 = (unsigned int *) ((char *) r4 + 0x18);
        *r1 = *r1 + *r0;
    }
    return;
}
