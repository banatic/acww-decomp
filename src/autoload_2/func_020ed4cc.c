/* func_020ed4cc @ 0x020ed4cc, 0x74 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern char *data_021fbf3c;
extern int func_ov065_022798d0(char *, char *, char *, char *, char *);

void func_020ed4cc(int x)
{
    char *base = data_021fbf3c;
    int off = x * 35;
    char tmp;
    int res;

    res = func_ov065_022798d0(base + x * 12, base + 417 + off, base + 418 + off, base + 384 + off, &tmp);
    (data_021fbf3c + 416)[off] = res;
}
