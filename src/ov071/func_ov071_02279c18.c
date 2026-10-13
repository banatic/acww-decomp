/* func_ov071_02279c18 @ 0x02279c18, 0x3c bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c67a4;
extern int data_021c67d0[3];
extern int func_ov071_02279c54(void *a, int *local, void *p, void *b);

int func_ov071_02279c18(void *a, void *b)
{
    int local[4];
    void *p = (char *) a + 0x5c;
    int result = 0;
    if (data_021c67a4) {
        local[0] = data_021c67d0[0];
        local[1] = data_021c67d0[1];
        local[2] = data_021c67d0[2];
        result = func_ov071_02279c54(a, local, p, b);
    }
    return result;
}
