/* scene_map_2: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204d5f8 @ 0x0204d5f8, 0x2c bytes, Thumb
 * func_0204d5c8 @ 0x0204d5c8, 0x2e bytes, Thumb
 * func_0204d594 @ 0x0204d594, 0x34 bytes, Thumb
 * func_0204d544 @ 0x0204d544, 0x4e bytes, Thumb
 * func_0204d530 @ 0x0204d530, 0x12 bytes, Thumb
 */

typedef struct {
    volatile void *unk_00;
} UnkStruct_0204d5f8;

struct UnkStruct_0204d594 {
    char pad_00[0x54];
    int *array;
    int count;
};

typedef struct {
    char pad_00[0x54];
    void **array;
    int count;
} UnkStruct_0204d544;

struct UnkStruct_0204d530 {
    char pad_00[0x54];
    int *arr;
    int limit;
};

extern void *func_020edf70(unsigned int size);
extern void *func_020ee660(void *);
extern char data_020da13c;
extern char data_020db898;
extern int func_0204e414(void);
extern int func_020b67e8(unsigned int);
extern int func_0204df08(int);
extern void *func_020e9948(void *heap, int size);
extern void func_020e993c(void *data, void *item);

void *func_0204d5f8(void)
{
    UnkStruct_0204d5f8 *obj;
    obj = (UnkStruct_0204d5f8 *) func_020edf70(0x5c);
    if (obj) {
        func_020ee660(obj);
        obj->unk_00 = (void *) &data_020da13c;
        obj->unk_00 = (void *) &data_020db898;
    }
    return (void *) obj;
}

int func_0204d5c8(int arg0)
{
    int r4;
    int r5;
    int result;

    r5 = arg0;
    r4 = 0;
    if (r5 == 0) {
        r4 = func_0204e414();
    } else {
        if (func_020b67e8(arg0) == 1) {
            r4 = func_0204df08(r5);
        }
    }
    return r4;
}

void func_0204d594(struct UnkStruct_0204d594 *self, void *heap)
{
    int i;

    if (self->count > 0) {
        self->array = func_020e9948(heap, self->count * 4);
        if (self->array) {
            i = 0;
            for (; i < self->count; i++) {
                self->array[i] = 0;
            }
        }
    }
}

void func_0204d544(UnkStruct_0204d544 *list, void *arg1)
{
    if (list->array != 0 && list->count > 0) {
        int i = 0;
        int zero = 0;
        for (; i < list->count; i++) {
            if (list->array[i] != 0) {
                func_020e993c(arg1, list->array[i]);
                list->array[i] = (void *) zero;
            }
        }
        func_020e993c(arg1, list->array);
        list->array = 0;
        list->count = 0;
    }
}

void func_0204d530(struct UnkStruct_0204d530 *obj, int value, int index)
{
    int *arr = obj->arr;
    if (arr != 0) {
        if (index < obj->limit) {
            arr[index] = value;
        }
    }
}
