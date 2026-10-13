/* func_02021fb8 @ 0x02021fb8, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern void *func_020984e8(void);
extern void *func_02099870(void *);
extern int func_02094ffc(void *);
extern void func_0208150c(void *);
extern int func_020036e8(void);
extern void func_0202da38(void *, void *, void *, int, int, int, int, int, int);
extern const char data_020c8ec4[];
extern const char data_020c8ec8[];

int func_02021fb8(void *obj)
{
    int idx = 2;
    if (func_020984e8() != 0) {
        idx = func_02094ffc(func_02099870(func_020984e8()));
    }
    if (idx >= 2) {
        idx = 1;
    }
    idx = idx * 8;
    func_0208150c(*(void **) (*(char **) ((char *) obj + 0x100) + 0x830));
    func_0202da38(obj, (char *) obj + 0x104, (char *) obj + 0x122, 0x1e, func_020036e8(), *(const int *) (data_020c8ec4 + idx),
                  *(const unsigned char *) (data_020c8ec8 + idx), 0, 0);
    return 1;
}
