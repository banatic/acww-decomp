/* func_02068924 @ 0x02068924, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020cce88[];
extern int func_0207f270(int arg);
extern int func_020794c4(int arg);

typedef struct UnkStructC UnkStructC;

typedef struct UnkTable {
    char pad_00[0x68];
    int (*func)(UnkStructC *);
} UnkTable;

struct UnkStructC {
    UnkTable *table;
};

typedef struct UnkStructB {
    char pad_00[0x14a8];
    UnkStructC *obj;
} UnkStructB;

typedef struct UnkStructA {
    char pad_00[4];
    UnkStructB *b;
} UnkStructA;

unsigned char func_02068924(UnkStructA *arg0)
{
    int idx = 0;
    UnkStructB *b;
    UnkStructC *obj;
    int result1;
    int result2;

    b = arg0->b;
    obj = b->obj;
    result1 = obj->table->func(obj);
    if (result1 != 0) {
        result2 = func_0207f270(result1);
        if (result2 != 0) {
            idx = func_020794c4(result2);
        }
    }
    return data_020cce88[idx];
}
