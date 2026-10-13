/* func_02060aac @ 0x02060aac, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02060aac UnkStruct_02060aac;
extern UnkStruct_02060aac data_021ebcd4;
extern void *func_02060f04(UnkStruct_02060aac *g, void *a);
extern void *func_02060ee0(UnkStruct_02060aac *g, unsigned int i);
extern unsigned short *func_02061188(void *x);
int func_02060aac(void *a, unsigned short *b)
{
    unsigned int i;
    UnkStruct_02060aac *g = &data_021ebcd4;
    void *e = func_02060f04(g, a);
    if (e != 0) {
        for (i = 0; i < 5; i++) {
            void *x = func_02060ee0(g, i);
            if (e != x) {
                unsigned short v = *func_02061188(x);
                if (v == *b) {
                    return 1;
                }
            }
        }
        return 0;
    }
    return 0;
}
