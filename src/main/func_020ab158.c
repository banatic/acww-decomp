/* func_020ab158 @ 0x020ab158, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205166c(void *ptr, unsigned int something);

typedef struct {
    unsigned char pad_00[8];
    void *arr[5];
} UnkStruct_020ab158;

void func_020ab158(UnkStruct_020ab158 *obj)
{
    unsigned int i;
    unsigned int something;
    i = 0;
    something = i;
    do {
        if (obj->arr[i] != 0) {
            func_0205166c(obj->arr[i], something);
        }
        i++;
    } while (i < 5);
}
