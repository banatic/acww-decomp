/* func_0207d634 @ 0x0207d634, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(unsigned short *p);
extern int func_020644cc(int x);
extern int func_0207cc54(int mask, int count, int max);

typedef struct {
    char pad_00[0x78c];
    unsigned short arr[10];
    char pad_7A0[0x30];
    unsigned short bitfield;
} UnkStruct_0207d634;

void func_0207d634(UnkStruct_0207d634 *self)
{
    unsigned short *p = self->arr;
    unsigned short mask = 0;
    int count = 0;
    int i;
    int n;

    self->bitfield = mask;
    for (i = 0; i < 10; i++) {
        if (func_0204bcdc(p) != 0) {
            mask |= (1 << i);
            count++;
        }
        p++;
    }

    n = count;
    if (count > 5) {
        n = 5;
    }
    if (n > 3) {
        n = func_020644cc(n - 2) + 3;
    }

    if (count > 0) {
        while (n > 0) {
            int res = func_0207cc54(mask, count, 10);
            if (res != -1) {
                self->bitfield |= (1 << res);
                mask &= ~(1 << res);
                count--;
            }
            n--;
        }
    }
}
