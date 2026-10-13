/* func_02083c30 @ 0x02083c30, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02083c30 UnkStruct_02083c30;
typedef struct MethodTable MethodTable;

typedef char *(*MethodFunc)(UnkStruct_02083c30 *, unsigned int);

struct MethodTable {
    char pad_00[0x10];
    MethodFunc method;
};

struct UnkStruct_02083c30 {
    MethodTable *mt;
    unsigned int count;
};

void func_02083c30(UnkStruct_02083c30 *s, unsigned int idx)
{
    if (idx < s->count) {
        char *ptr = s->mt->method(s, idx);
        if (ptr != 0) {
            *ptr = 0;
        }
    }
}
