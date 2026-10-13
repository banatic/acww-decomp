/* func_020aac68 @ 0x020aac68, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02051694(void *);

typedef struct {
    unsigned int pad_00[5];
    void *arr[5];
} StructAAC68;

void func_020aac68(StructAAC68 *s)
{
    unsigned int i;
    for (i = 0; i < 5; i++) {
        if (s->arr[i]) {
            func_02051694(s->arr[i]);
        }
    }
}
