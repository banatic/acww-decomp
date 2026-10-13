/* func_0201c0e0 @ 0x0201c0e0, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073d90(int g);
extern unsigned char *func_02085148(void *p);
extern int func_020a7278(void);

int func_0201c0e0(void *selfv)
{
    unsigned char *self = (unsigned char *) selfv;
    int g;
    unsigned char *rec;
    int result;

    g = data_020ccf94;
    if (func_02073d90(g) == 0) {
        goto result1;
    }
    if (self[0x563] != 0) {
        goto result1;
    }

    rec = func_02085148(self + 0xea);
    if (rec == 0) {
        goto result0;
    }
    if (rec[0] == 0) {
        goto result0;
    }

    if ((rec[1] == 4 && func_020a7278() != 0) || rec[1] == *(int *) ((unsigned char *) g + 0x64)) {
        result = 1;
    } else {
        result = 0;
    }
    return result;

result0:
    result = 0;
    return result;
result1:
    result = 1;
    return result;
}
