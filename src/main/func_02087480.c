/* func_02087480 @ 0x02087480, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
} Pair;

extern int func_0206f798(void *arg);
extern int func_0206f7a4(void);
extern void func_0209e474(Pair *p);
extern void func_02087500(void *arg, int n);
extern void func_02087358(void *arg, Pair *p);
extern void func_02087274(void *arg, Pair *p);

void func_02087480(void *arg)
{
    Pair pos;
    if (func_0206f798(arg) || func_0206f7a4()) {
        pos.x = 0;
        pos.y = 0;
        func_0209e474(&pos);
        func_02087500(arg, 1);
        func_02087358(arg, &pos);
        func_02087274(arg, &pos);
    }
}
