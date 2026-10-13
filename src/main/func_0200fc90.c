/* func_0200fc90 @ 0x0200fc90, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short lo;
    unsigned short hi;
} UnkStruct_0200fc90;

extern void func_020110c4(void *, void *);
extern int func_0200f290(void *, int);
extern int func_0204bcdc(void *);
extern int func_0204bc64(void *);
extern int func_02062148(void *);

int func_0200fc90(void *arg0)
{
    UnkStruct_0200fc90 s;
    int flag;

    func_020110c4(&s, arg0);

    if (func_0200f290(arg0, 0) != 0) {
        if (func_0204bcdc(&s) != 0) {
            s.hi = 0xfff1;
            flag = (func_0204bc64(&s) == func_0204bc64(&s.hi));
        } else {
            flag = (s.lo == 0xfff1);
        }

        if (flag == 0) {
            return func_02062148(&s) + 1;
        }
    }

    return 0;
}
