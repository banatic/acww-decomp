/* func_02054094 @ 0x02054094, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02054094 UnkStruct_02054094;
typedef void (*Method)(UnkStruct_02054094 *);
typedef struct VTable {
    Method method;
} VTable;
struct UnkStruct_02054094 {
    VTable *vtable;
};
extern UnkStruct_02054094 *data_021c8ca0;
extern void func_020898e8(void);
extern void func_02002ec0(void);
extern void func_02002408(void);

void func_02054094(void)
{
    func_020898e8();
    if (data_021c8ca0) {
        data_021c8ca0->vtable->method(data_021c8ca0);
    }
    func_02002ec0();
    func_02002408();
}
