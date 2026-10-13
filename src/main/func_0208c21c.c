/* func_0208c21c @ 0x0208c21c, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a0c8(void *);
extern int func_0208a160(void *);
extern void func_0208c3b8(void *);

typedef struct Elem {
    char data[20];
} Elem;

typedef struct UnkStruct_0208c21c {
    char pad_00[0xc];
    Elem arr[9];
} UnkStruct_0208c21c;

void func_0208c21c(UnkStruct_0208c21c *s)
{
    int flag = 1;
    int zero = 0;
    int i;
    for (i = 0; i < 9; i++) {
        Elem *e = &s->arr[i];
        func_0208a0c8(e);
        if (func_0208a160(e) == 0) {
            flag = zero;
        }
    }
    if (flag) {
        func_0208c3b8(s);
    }
}
