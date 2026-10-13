/* func_0207a404 @ 0x0207a404, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *);
extern void *func_020617d8(int);

typedef struct UnkStruct_0207a404 {
    unsigned char *p;
    unsigned char n;
} UnkStruct_0207a404;

int func_0207a404(void)
{
    int local[2];
    UnkStruct_0207a404 *b;
    unsigned char *q;
    int prev;
    int i;
    int n;

    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    b = (UnkStruct_0207a404 *) func_020617d8(((unsigned char *) local)[4] - 1);
    if (b != 0) {
        q = b->p;
        prev = 0;
        i = 0;
        n = b->n;
        while (i < n) {
            if (q[0] == 0x30) {
                return q[1] - prev;
            }
            prev = q[1];
            q += 2;
            i++;
        }
    }
    return 0;
}
