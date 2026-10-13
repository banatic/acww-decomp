/* func_ov079_02279934 @ 0x02279934, 0x22 bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov079_02279958(void *param);

int func_ov079_02279934(void *param)
{
    int result;
    void *field;

    field = *(void **) ((char *) param + 0x98);
    if (field != 0) {
        result = func_ov079_02279958(param);
        if (result != 0) {
            return 1;
        }
    }
    return 0;
}
