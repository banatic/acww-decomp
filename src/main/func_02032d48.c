/* func_02032d48 @ 0x02032d48, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[36];
} Elem;

typedef struct {
    unsigned int count;
    Elem arr[1];
} UnkStruct_02032d48;

extern int func_02032fc0(Elem *a, int arg, Elem *b);

void func_02032d48(UnkStruct_02032d48 *self, int arg)
{
    unsigned int n = self->count;
    Elem *p = &self->arr[0];
    unsigned int i = 0;
    unsigned int start = 0;
    while (i < n) {
        Elem *q = &self->arr[0];
        unsigned int j = start;
        while (j < n) {
            func_02032fc0(p, arg, q);
            q++;
            j++;
        }
        p++;
        i++;
    }
}
