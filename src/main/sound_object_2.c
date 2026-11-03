/* sound_object_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02003ec8 @ 0x02003ec8, 0x174 bytes, Thumb
 * func_02003ea0 @ 0x02003ea0, 0x28 bytes, Thumb
 * func_02003e90 @ 0x02003e90, 0x10 bytes, Thumb
 * func_02003e80 @ 0x02003e80, 0x10 bytes, Thumb
 */

struct UnkStruct_02003e90;

struct Vtbl {
    void (*func)(struct UnkStruct_02003e90 *);
};

struct UnkStruct_02003e90 {
    struct Vtbl *vtbl;
};

struct UnkStruct_02003e80 {
    int pad_00;
    void *(*func)(void *);
};

struct UnkStruct_02003e80_2 {
    struct UnkStruct_02003e80 *inner;
};

extern void *func_020e9948(void *heap, unsigned int size);
extern unsigned char data_0213f0b0[];
extern unsigned char data_0213f0d0[];
extern unsigned char data_0213f0f0[];
extern unsigned char data_0213f110[];
extern unsigned char data_0213f130[];
extern unsigned char data_0213f150[];
extern unsigned char data_0213f170[];
extern unsigned char data_0213f190[];
extern unsigned char data_0213f1b0[];
extern unsigned char data_0213f1d0[];
extern unsigned char data_0213f1f0[];
extern unsigned char data_0213f210[];
extern unsigned char data_0213f230[];
extern unsigned int data_020c7590[];
extern unsigned int data_020c75c0[];

void *func_02003ec8(void *heap, int kind)
{
    void *obj;

    switch (kind) {
        case 0:
            obj = func_020e9948(heap, 0x10);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f0b0;
            }
            break;
        case 1:
            obj = func_020e9948(heap, 0x10);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f0d0;
            }
            break;
        case 2:
            obj = func_020e9948(heap, 0x10);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f0f0;
            }
            break;
        case 3:
            obj = func_020e9948(heap, 0x10);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f110;
            }
            break;
        case 4:
            obj = func_020e9948(heap, 0x14);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f230;
            }
            break;
        case 5:
            obj = func_020e9948(heap, 0x10);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f130;
            }
            break;
        case 6:
            obj = func_020e9948(heap, 0x10);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f1b0;
            }
            break;
        case 7:
            obj = func_020e9948(heap, 0x18);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f1d0;
            }
            break;
        case 8:
            obj = func_020e9948(heap, 0x14);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f1f0;
            }
            break;
        case 9:
            obj = func_020e9948(heap, 0x10);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f150;
            }
            break;
        case 10:
            obj = func_020e9948(heap, 0x14);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f210;
            }
            break;
        case 255:
            obj = func_020e9948(heap, 0x10);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f170;
            }
            break;
        default:
            obj = func_020e9948(heap, 0x10);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f0b0;
            }
            break;
    }
    return obj;
}

unsigned int func_02003ea0(void)
{
    unsigned int max = 0;
    unsigned int *p = data_020c7590;

    while (p < data_020c75c0) {
        if (*p > max) {
            max = *p;
        }
        p++;
    }

    return (max + 3) & ~3;
}

void func_02003e90(struct UnkStruct_02003e90 *obj)
{
    obj->vtbl->func(obj);
}

void *func_02003e80(struct UnkStruct_02003e80_2 *self)
{
    return self->inner->func(self);
}
