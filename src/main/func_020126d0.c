/* func_020126d0 @ 0x020126d0, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} UnkStruct_020126d0;
typedef struct {
    int pad_00;
    int v1;
    int v2;
} UnkStruct_020126d0_2;

extern UnkStruct_020126d0_2 *data_021c80bc;
extern int func_020644cc(int a);
extern void func_020131dc(UnkStruct_020126d0 *out, void *param1, UnkStruct_020126d0 *computed, UnkStruct_020126d0_2 *g);

void func_020126d0(UnkStruct_020126d0 *out, void *param1)
{
    UnkStruct_020126d0_2 *g = data_021c80bc;

    out->a = 0;
    out->b = 0;
    if (g != 0) {
        char *base = (char *) g + 4;
        int v1 = *(int *) base;
        int v2 = *(int *) (base + 4);
        UnkStruct_020126d0 computed;
        UnkStruct_020126d0 local;

        computed.a = 0;
        computed.b = 0;
        if (v1 >= 3) {
            computed.a = func_020644cc(v1 - 2) + 1;
        }
        if (v2 >= 3) {
            computed.b = func_020644cc(v2 - 2) + 1;
            func_020131dc(&local, param1, &computed, g);
            out->a = local.a;
            out->b = local.b;
        }
    }
}
