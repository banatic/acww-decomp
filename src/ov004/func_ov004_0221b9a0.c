/* func_ov004_0221b9a0 @ 0x0221b9a0, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char data_021f38f8[];
extern int func_02071298(void *a, unsigned short *v);

void func_ov004_0221b9a0(void *self)
{
    unsigned short v;
    unsigned int i;

    i = *((unsigned char *) self + 0x155) + 1;
    for (; i < *(unsigned int *) ((char *) self + 0x168); i++) {
        v = (*(unsigned short **) ((char *) self + 0x164))[i];
        if (func_02071298(data_021f38f8, &v) != 0) {
            *((unsigned char *) self + 0x155) = (unsigned char) i;
            return;
        }
    }
    *((unsigned char *) self + 0x155) = (unsigned char) *(unsigned int *) ((char *) self + 0x168);
}
