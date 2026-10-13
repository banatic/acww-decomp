/* func_0206c0f0 @ 0x0206c0f0, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205166c(void *ptr, int val);

typedef struct {
    char pad_00[0x420];
    void *array[3];
} UnkStruct_0206c0f0;

typedef struct {
    char pad_00[0x10];
    int unk_10;
} Elem;

void func_0206c0f0(UnkStruct_0206c0f0 *param0)
{
    int zero = 0;
    unsigned int i = 0;
    do {
        Elem *elem = (Elem *) param0->array[i];
        if (elem != 0) {
            func_0205166c(elem, zero);
            elem->unk_10 = 0;
        }
        i++;
    } while (i < 3);
}
