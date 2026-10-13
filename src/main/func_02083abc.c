/* func_02083abc @ 0x02083abc, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char *func_02083b00(void);
extern void func_02083ba0(char *p, int a, int b);
extern int data_020d0638[];
struct UnkStruct_02083abc {
    int unk_00;
    unsigned int count;
};
void func_02083abc(struct UnkStruct_02083abc *s, unsigned int n)
{
    int i;
    int delta;
    if (n >= s->count) {
        return;
    }
    i = 0;
    delta = n * 4;
    for (; i < 3; i++) {
        char *p;
        func_02083ba0(func_02083b00() + 8 + delta, n + data_020d0638[i], i);
        p = func_02083b00() + 8;
        p += delta;
        *p = 1;
    }
}
