/* func_02099f1c @ 0x02099f1c, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void);
extern void func_02099fe0(void *);
extern void *func_02099734(void *);
extern void *func_02098f48(void *, int);
extern int func_02098e74(void *, int);

typedef struct {
    unsigned short bits;
    unsigned char count;
} FlagStruct;

int func_02099f1c(FlagStruct *flags, int (*cb)(unsigned short *))
{
    void *v8;
    unsigned short *arr;
    int i;

    v8 = func_020984e8();
    func_02099fe0(flags);
    arr = (unsigned short *) func_02098f48(func_02099734(v8), 0);
    for (i = 0; i < 15; i++) {
        if (func_02098e74(func_02099734(v8), i) && cb(&arr[i])) {
            flags->bits |= (1 << i);
            flags->count++;
        }
    }
    return flags->count;
}
