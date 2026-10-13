/* func_ov073_0227964c @ 0x0227964c, 0x4c bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

typedef void *(*FuncType)(void *);

extern unsigned char data_ov073_02279c1c[];
extern unsigned char data_ov073_02279c14[];

void *func_ov073_0227964c(void *self)
{
    char *s = (char *) self;
    unsigned int off;
    char *p;
    int adj;
    FuncType func;
    void *result = 0;

    off = (*(unsigned int *) (s + 0x654)) << 4;
    if (*(unsigned int *) (data_ov073_02279c1c + off) != 0) {
        p = (char *) data_ov073_02279c14 + off + 8;
        adj = *(int *) (p + 4);
        s += adj >> 1;
        if (adj & 1) {
            func = *(FuncType *) ((char *) (*(void **) s) + (unsigned int) *(unsigned int *) p);
        } else {
            func = *(FuncType *) p;
        }
        result = func((void *) s);
    }
    return result;
}
