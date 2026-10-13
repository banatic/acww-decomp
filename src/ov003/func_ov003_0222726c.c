/* func_ov003_0222726c @ 0x0222726c, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0223bd90;
extern void *data_ov003_0223cf74;
int func_02055324(void *p, void *t, void *g);
int func_020552ec(void *p, void *e);
void *func_0206223c(int i, int k);

int func_ov003_0222726c(char *self)
{
    int r = 0;
    int i;
    if (func_02055324(self + 0x4ae0, &data_ov003_0223bd90, data_ov003_0223cf74) != 0) {
        for (i = 0; i < 0x49; i++) {
            *(int *) (self + i * 4 + 0x50) = func_020552ec(self + 0x4ae0, func_0206223c(i, 1));
        }
        r = 1;
    }
    return r;
}
