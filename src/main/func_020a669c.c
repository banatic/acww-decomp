/* func_020a669c @ 0x020a669c, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x3c];
    unsigned char arr[4][8];
} UnkStruct_020a669c;

extern void *data_020ccf94;
extern void func_020a7778(void *a0, void *a1, void *a2, void *a3, void *a4);
extern void func_020a7394(int a0, unsigned char a1, unsigned char a2, unsigned char a3, int a4);
extern void *func_020a7820(void *a0);
extern void func_020a77f4(void *a0, int a1, unsigned char a2, unsigned char a3, unsigned char a4, int a5);
extern void func_02073820(void *a0);
extern void func_020737f0(void *a0, void *a1, int a2);
extern void func_02073770(void *a0, int a1, int a2);
extern void func_020a7768(void *a0);
extern int func_020a7810(void *a0);

void func_020a669c(UnkStruct_020a669c *self)
{
    unsigned char local[8];
    int val;
    unsigned int i = 0;
    void *r4 = data_020ccf94;
    void *ptr;

    do {
        ptr = &self->arr[i];
        func_020a7778(ptr, &local[0], &local[1], &local[2], &val);
        if (val != 0) {
            func_020a7394(i, local[0], local[1], local[2], val);
            func_020a7820(&local[3]);
            func_020a77f4(&local[3], i, local[0], local[1], local[2], val);
            func_02073820(r4);
            func_020737f0(r4, &local[3], 2);
            func_02073770(r4, 9, 4);
            func_020a7768(ptr);
            func_020a7810(&local[3]);
        }
        i++;
    } while (i < 4);
}
