/* func_ov004_0221ba88 @ 0x0221ba88, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char data_021f38f8[];
extern int func_02071298(void *a, unsigned short *v);

int func_ov004_0221ba88(void *self)
{
    unsigned short v;
    unsigned int i;

    for (i = 0; i < *(unsigned int *) ((char *) self + 0x168); i++) {
        v = (*(unsigned short **) ((char *) self + 0x164))[i];
        if (func_02071298(data_021f38f8, &v) != 0) {
            return 1;
        }
    }
    return 0;
}
