/* func_ov104_0229c7e8 @ 0x0229c7e8, 0x88 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[0x100];
} Entry;

extern int func_020978bc(Entry *p, int n);
extern int func_02065ec0(Entry *p);
extern int func_02065e9c(Entry *p);
extern int func_020979ac(Entry *p);
extern int func_ov104_0229c7dc(int a, Entry *p);
extern void func_02066650(Entry *p);

unsigned short func_ov104_0229c7e8(int a, Entry *p)
{
    int count, i;
    unsigned short flags = 0;

    count = func_020978bc(p, 0xa);
    if (count == 0) {
        return flags;
    }

    for (i = 0; i < count; i++) {
        if (func_02065ec0(p) != 1) {
            func_02066650(p);
        } else {
            if (func_02065e9c(p) == 0) {
                if (func_020979ac(p) != 0) {
                    if (func_ov104_0229c7dc(a, p) != 0) {
                        func_02066650(p);
                        flags |= 0x200;
                    } else {
                        flags |= 0x20;
                    }
                }
            }
        }
        p++;
    }

    return flags;
}
