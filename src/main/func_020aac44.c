/* func_020aac44 @ 0x020aac44, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x14];
    unsigned int arr[5];
} UnkStruct_020aac44;

extern void func_0205166c(unsigned int, unsigned int);

void func_020aac44(UnkStruct_020aac44 *p)
{
    unsigned int i;
    unsigned int zero = 0;
    unsigned int val;
    for (i = 0; i < 5; i++) {
        val = p->arr[i];
        if (val) {
            func_0205166c(val, zero);
        }
    }
}
