/* func_020aac1c @ 0x020aac1c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x14];
    int arr[5];
} Func020aac1cStruct;

extern void func_020a8fb8(int arg);

void func_020aac1c(Func020aac1cStruct *s)
{
    unsigned int i;
    for (i = 0; i < 5; i++) {
        if (s->arr[i]) {
            func_020a8fb8(s->arr[i]);
            s->arr[i] = 0;
        }
    }
}
