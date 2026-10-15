/* func_02067fa4 @ 0x02067fa4, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b45d0(char *p1, unsigned char p2, int p3, int p4, int p5, int p6);

struct func_02067fa4_s {
    char pad_00[0x1a6a];
    unsigned char b;
    char pad_1A6B[0x185];
    char arr[1];
};

char *func_02067fa4(struct func_02067fa4_s *self)
{
    func_020b45d0(self->arr, self->b, 2, 0, 9, 0);
    return self->arr;
}
