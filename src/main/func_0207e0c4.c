/* func_0207e0c4 @ 0x0207e0c4, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef int (*Fn)(int, int, int);
typedef struct UnkStruct_0207e0c4 {
    signed char kind;
    char pad_01[3];
    Fn fn;
} UnkStruct_0207e0c4;

extern UnkStruct_0207e0c4 data_020cd5c4[];
extern int func_02099870(int);
extern int func_020950c0(signed char *);

int func_0207e0c4(int a, int b, int c)
{
    UnkStruct_0207e0c4 *e;
    int k;
    int res;
    int i;

    k = func_020950c0((signed char *) func_02099870(a));
    e = data_020cd5c4;
    res = 0x58;
    for (i = 0; i < 0x58; i++) {
        if (e->kind == 2 || e->kind == k) {
            if (e->fn(a, b, c) != 0) {
                res = (unsigned char) i;
                goto done;
            }
        }
        e++;
    }
done:
    return res;
}
