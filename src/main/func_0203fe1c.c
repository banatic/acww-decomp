/* func_0203fe1c @ 0x0203fe1c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *);
extern void func_0203fe58(int);
typedef struct {
    unsigned char zero;
    unsigned char a;
    unsigned char b;
} UnkStruct_0203fe1c;
extern UnkStruct_0203fe1c data_021c74d0;
typedef union {
    struct {
        unsigned int word0;
        unsigned int word1;
        unsigned int word2;
    } words;
    struct {
        unsigned char pad0[3];
        unsigned char a;
        unsigned char b;
        unsigned char c;
        unsigned char pad1[6];
    } bytes;
} LocalUnion;
void func_0203fe1c(int arg)
{
    LocalUnion local;
    int ok;
    local.words.word0 = 0;
    local.words.word1 = 0;
    func_0209e474(&local);
    ok = local.bytes.c == data_021c74d0.b && local.bytes.b == data_021c74d0.a && local.bytes.a == data_021c74d0.zero;
    if (ok) {
        return;
    }
    func_0203fe58(0);
}
