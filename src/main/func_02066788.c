/* func_02066788 @ 0x02066788, 0xa6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02094fd4(void *);
extern void *func_02094f7c(void *);
extern int func_02003780(void *);
extern void *func_02070c08(void *);
extern int func_02051c08(void *, void *, int);
extern void func_020037ac(void *, void *);
extern int func_02003618(void *, void *);
extern int func_020a87e0(void *, void *);
extern void func_02094f34(void *, void *, int);
extern int func_0207094c(void *, int);
extern void func_020708b4(void *, void *);
extern int **func_02070be8(void *);
extern int func_02003750(void *);
extern void *func_02094f64(void *);
extern void *func_02094fbc(void *);

typedef struct {
    unsigned char pad_00[0x10];
    unsigned char data[6];
    unsigned char pad_16[0x8];
    unsigned char type;
} UnkStruct_02066788;

void *func_02066788(UnkStruct_02066788 *s, void *arg1)
{
    unsigned char obj0[0x20];
    unsigned char obj1[0x1c];
    unsigned char obj2[0x10];
    unsigned char obj3[0x70];

    func_02094fd4(obj0);
    func_02094f7c(obj1);
    func_02003780(obj2);
    func_02070c08(obj3);

    switch (s->type) {
        case 1:
        case 2:
            func_02051c08(s->data, arg1, 6);
            break;
        case 3:
            func_020037ac(obj2, s);
            func_02003618(obj2, obj0);
            func_020a87e0(obj1, obj0);
            func_02094f34(obj1, arg1, 6);
            break;
        case 7:
            func_0207094c(obj3, 0x43);
            func_020708b4(obj3, arg1);
            break;
        default:
            break;
    }

    func_02070be8(obj3);
    func_02003750(obj2);
    func_02094f64(obj1);
    return func_02094fbc(obj0);
}
