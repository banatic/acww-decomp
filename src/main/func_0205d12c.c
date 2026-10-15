/* func_0205d12c @ 0x0205d12c, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *data_020ccf94;
extern void *data_021c9ae8;
extern int func_0205d200(void);
extern int func_0205d1fc(void);
extern int func_0205d1f8(void);
extern int func_02055c80(void *dst, int a, int b, int c);
extern int func_0205d208(void);
extern int func_020e9968(void *a, int b, int c);

typedef struct {
    char pad_00[20];
} Elem;

typedef struct {
    int arr[4];
    Elem elems[8];
} UnkStruct_0205d12c;

void func_0205d12c(UnkStruct_0205d12c *obj)
{
    unsigned int count;
    unsigned int i;
    int v1;
    int v2;
    int v3;
    void *base;

    count = data_020ccf94[0x6c];

    for (i = 0; i < count; i++) {
        v1 = func_0205d200();
        v2 = func_0205d1fc();
        v3 = func_0205d1f8();
        func_02055c80(&obj->elems[i], v1, v2, v3);
    }

    base = data_021c9ae8;
    for (i = 0; i < count; i++) {
        obj->arr[i] = func_020e9968(base, func_0205d208(), 4);
    }
}
