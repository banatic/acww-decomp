/* func_ov003_02211d3c @ 0x02211d3c, 0x10 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov003_02211d3c(void *r0, char r1, void *r2);

void *func_ov003_02211d3c(void *r0, char r1, void *r2)
{
    *(char *) r0 = r1;
    *(int *) ((char *) r0 + 4) = *(int *) r2;
    *(int *) ((char *) r0 + 8) = *(int *) ((char *) r2 + 4);
    *(int *) ((char *) r0 + 12) = *(int *) ((char *) r2 + 8);
    return r0;
}
