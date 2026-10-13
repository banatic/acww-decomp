/* func_ov003_02226438 @ 0x02226438, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0223bd58;
extern void *data_ov003_02239d60[];
extern void *data_ov003_0223cf74;
int func_02055324(void *p, void *t, void *g);
int func_020552ec(void *p, void *e);

int func_ov003_02226438(char *self)
{
    int r = 0;
    int i;
    if (func_02055324(self + 0x4af0, &data_ov003_0223bd58, data_ov003_0223cf74) != 0) {
        for (i = 0; i < 2; i++) {
            int k = i * 4;
            *(int *) (self + k + 0x3060) = func_020552ec(self + 0x4af0, *(void **) ((char *) data_ov003_02239d60 + k));
        }
        r = 1;
    }
    return r;
}
