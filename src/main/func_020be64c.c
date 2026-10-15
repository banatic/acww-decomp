/* func_020be64c @ 0x020be64c, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef union {
    int a;
    int b;
} UnkStruct_020be64c;

typedef struct {
    UnkStruct_020be64c u;
    int y;
    int z;
} Elem;

typedef struct {
    Elem array1[8];
    Elem array2[8];
    char flag;
} UnkStruct_020be64c_2;

extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void func_020012dc(void *);
extern void func_020012e8(void *);

extern unsigned char data_0213efe8[];
extern unsigned char data_0213f03c[];

UnkStruct_020be64c_2 *func_020be64c(UnkStruct_020be64c_2 *obj)
{
    Elem *p;

    p = obj->array1;
    do {
        p->u.a = (unsigned int) data_0213efe8;
        p->u.b = (unsigned int) data_0213f03c;
        p++;
    } while (p != &obj->array1[8]);

    __cxa_vec_ctor((void *) (&obj->array2[0]), 8, 12, (void (*)(void *)) func_020012e8, (void (*)(void *)) func_020012dc);

    obj->flag = 0;

    for (p = obj->array2; p < &obj->array2[8]; p++) {
        p->u.a = 0;
        p->y = 0;
        p->z = 0;
    }

    return obj;
}
