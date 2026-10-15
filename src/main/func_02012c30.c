/* func_02012c30 @ 0x02012c30, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02012c68(void *a, void *b, void *map);
extern int func_02013518(void *a, void *b);
extern void *data_021c80bc;

int func_02012c30(void *a, void *b)
{
    if (data_021c80bc != 0) {
        func_02012c68(a, b, data_021c80bc);
        if (func_02013518(a, b) != 0) {
            ((int *) a)[1] = 2;
            return 1;
        }
    }
    return 0;
}
