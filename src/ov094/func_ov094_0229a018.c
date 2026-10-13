/* func_ov094_0229a018 @ 0x0229a018, 0x20 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9ccc(void *);

typedef struct {
    char data[0x38];
} Unit;

typedef struct {
    char pad_00[0x38];
    Unit units[3];
} Container;

void func_ov094_0229a018(Container *c)
{
    int i;
    for (i = 0; i < 3; i++) {
        func_020b9ccc(&c->units[i]);
    }
}
