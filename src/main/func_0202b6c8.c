/* func_0202b6c8 @ 0x0202b6c8, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099870(int);
extern int func_02080404(unsigned int, unsigned int *, int, int);
extern int func_02021d60(int a, int b);

extern int func_02021ea8(void *self, int *arr, int count, void *predicate);
extern unsigned int func_0208150c(unsigned int);
extern int func_020036e8(unsigned char *);
extern int func_0202da38(void *, void *, void *, int, int, int, int, int, int);

extern struct {
    unsigned int w;
    unsigned char b;
} data_020c89c8;

int func_0202b6c8(void *self)
{
    unsigned int val;
    unsigned int arr[8];
    int flag;
    int i;
    int res;
    int t;

    val = *(unsigned int *) ((char *) *(void **) ((char *) self + 0x100) + 0x830);
    flag = 0;
    for (i = flag; i < 8; i++) {
        arr[i] = 0;
    }

    res = func_02080404(val, arr, func_02099870((int) func_020984e8()), 2);
    if (res > 0) {
        *(unsigned int *) ((char *) self + 0x138) =
            func_02021ea8((void *) (val), (int *) (arr), (int) (res), (((void *) func_02021d60)));
    }

    if (*(unsigned int *) ((char *) self + 0x138) == 0) {
        flag = 1;
    }

    t = func_020036e8(
        (unsigned char *) func_0208150c(*(unsigned int *) ((char *) *(void **) ((char *) self + 0x100) + 0x830)));
    func_0202da38(self, (char *) self + 0x104, (char *) self + 0x122, 30, t, data_020c89c8.w, data_020c89c8.b, flag, 0);

    return 1;
}
