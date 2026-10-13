/* func_020829ec @ 0x020829ec, 0x56 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02082b60(void *a, void *b);
extern void func_0204f818(int *a, int *b, char *c);

typedef struct {
    void *ptr;
    void *pad_04;
} Elem;

void *func_020829ec(Elem *arr, int find1, int find2)
{
    void *result = 0;
    Elem *p = arr;
    int a = 0;
    int b = 0;
    int i;

    for (i = 0; i < 8; p++, i++) {
        if (func_02082b60(arr, p)) {
            func_0204f818(&a, &b, (char *) p->ptr + 0x5c);
            if (a == find1 && b == find2) {
                result = p->ptr;
                break;
            }
        }
    }
    return result;
}
