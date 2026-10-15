/* func_020397a0 @ 0x020397a0, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020da5d8;
extern void *func_0203a1f8(void *);
extern void *func_0203a23c(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));

typedef struct {
    void *unk_00;
    char data[0x2e0];
    int arr_one[4];
    int arr_two[4];
} UnkStruct_020397a0;

UnkStruct_020397a0 *func_020397a0(UnkStruct_020397a0 *obj)
{
    int i;
    obj->unk_00 = (void *) &data_020da5d8;
    __cxa_vec_ctor((void *) (obj->data), 4, 0xb8, (((void (*)(void *)) func_0203a23c)), (((void (*)(void *)) func_0203a1f8)));
    for (i = 0; i < 4; i++) {
        obj->arr_one[i] = 0;
        obj->arr_two[i] = 0;
    }
    return obj;
}
