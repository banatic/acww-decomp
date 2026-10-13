/* func_ov088_02279640 @ 0x02279640, 0x38 bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c67a4;
extern int data_021c67d0[3];
extern int func_ov088_02279678(void *p, int *d, char *f, int v);

int func_ov088_02279640(void *param)
{
    char *field = (char *) param + 0x5c;
    int local[3];
    int result = 0;

    if (data_021c67a4) {
        local[0] = data_021c67d0[0];
        local[1] = data_021c67d0[1];
        local[2] = data_021c67d0[2];

        result = func_ov088_02279678(param, local, field, local[1]);
    }

    return result;
}
