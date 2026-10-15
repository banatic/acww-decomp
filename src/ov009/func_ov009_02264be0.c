/* func_ov009_02264be0 @ 0x02264be0, 0x30 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_022203dc(void);
extern int func_02064328(char *, const char *, ...);

typedef struct {
    char pad_00[0x138];
    int unk_138;
} UnkStruct_02264be0;

extern char data_ov009_02265b74[];
extern char data_ov009_02265ad4[];

char *func_ov009_02264be0(UnkStruct_02264be0 *s)
{
    int val = s->unk_138;
    func_02064328(data_ov009_02265b74, data_ov009_02265ad4, val, val, func_ov003_022203dc());
    return data_ov009_02265b74;
}
