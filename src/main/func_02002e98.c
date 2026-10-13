/* func_02002e98 @ 0x02002e98, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned long long d[6];
} DataType;
extern DataType data_0213fee4;
extern char data_0213feb4[];
extern void MTX_Inverse43(void *, void *);

void func_02002e98(const DataType *src)
{
    data_0213fee4 = *src;
    MTX_Inverse43(&data_0213fee4, data_0213feb4);
}
