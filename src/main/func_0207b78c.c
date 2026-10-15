/* func_0207b78c @ 0x0207b78c, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073d90(int);
extern int func_0207cad4(void *);
extern int func_0208150c(void *);
extern int func_02003704(int);
extern int func_0207b810(void *, void *, int);
extern int func_0209bd10(unsigned int object);

int func_0207b78c(void *param)
{
    int forwarded_value;

    int result;
    int count5;
    int count4;
    int i;
    int v8;
    void *p;

    if (func_02073d90(data_020ccf94) != 0) {
        return 0;
    }

    p = param;
    result = func_0207cad4(p);
    count5 = 0;
    count4 = 0;
    i = 0;
    v8 = 0;

    do {
        if (func_02003704(func_0208150c(p)) != 0) {
            if ((forwarded_value = (int) func_0207b810(param, p, v8)) == 0x16) {
                count5++;
            } else if (func_0209bd10((unsigned int) forwarded_value) != 1) {
                count4++;
            }
        }
        p = (char *) p + 0x7ec;
        i++;
    } while (i < 8);

    if (result < count4) {
        goto ret0;
    }
    if (((result - count4) >> 1) >= count5) {
        goto ret0;
    }
    return 1;

ret0:
    return 0;
}
