/* func_020f5970 @ 0x020f5970, 0x18 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern char data_0213f074;

typedef struct {
    void *p;
    char pad_04[0x3a];
    char flag;
} UnkStruct_020f5970;

void func_020f5970(UnkStruct_020f5970 *s)
{
    s->p = &data_0213f074;
    s->flag = 0;
}
