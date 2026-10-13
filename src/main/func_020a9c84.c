/* func_020a9c84 @ 0x020a9c84, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int arr[6];
    int x;
} __func_020a9c84_struct;

void func_020a9c84(__func_020a9c84_struct *p)
{
    unsigned int i;
    p->x = 0;
    for (i = 0; i < 6; i++) {
        p->arr[i] = 0;
    }
}
