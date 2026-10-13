/* func_0207fbb4 @ 0x0207fbb4, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x78c];
    unsigned short arr[1];
} UnkStruct_0207fbb4;

extern int func_0207ffa0(UnkStruct_0207fbb4 *, int);
extern int func_0207fc34(UnkStruct_0207fbb4 *, unsigned short *, int);
extern int func_0207cc54(int, int, int);

int func_0207fbb4(UnkStruct_0207fbb4 *arg0, int b, int c, int d)
{
    if (func_0207ffa0(arg0, c) != 0) {
        unsigned short *p = &arg0->arr[c];
        unsigned short mask = 0;
        int count = 0;
        while (c < d) {
            if (func_0207ffa0(arg0, c) != 0) {
                if (*p != 0xfff1) {
                    if (func_0207fc34(arg0, p, b) == 0) {
                        mask |= 1 << c;
                        count++;
                    }
                }
            }
            p++;
            c++;
        }
        return func_0207cc54(mask, count, 10);
    } else {
        return -1;
    }
}
