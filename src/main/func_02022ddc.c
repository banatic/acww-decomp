/* func_02022ddc @ 0x02022ddc, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int x);
extern int func_020036e8(int x);

typedef struct {
    char pad_00[0x830];
    unsigned int value;
} inner_t;

typedef struct {
    char pad_00[0x100];
    inner_t *ptr;
    char arr[30];
} outer_t;

extern struct {
    unsigned int val;
    unsigned char byte;
} data_020c8a10;

extern void func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);

int func_02022ddc(outer_t *obj)
{
    func_0202da38(obj, obj->arr, obj->arr + 30, 30, func_020036e8(func_0208150c(obj->ptr->value)), data_020c8a10.val,
                  data_020c8a10.byte, 0, 0);
    return 1;
}
