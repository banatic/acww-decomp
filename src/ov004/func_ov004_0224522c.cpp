/* func_ov004_0224522c @ 0x0224522c, 0x12c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern void *data_021c80bc;
extern unsigned char data_021f38f8[], data_ov004_0225f754[], data_ov004_0225f634[];
extern unsigned int data_ov004_0225f53c, data_ov004_0225f540;
extern unsigned short data_ov004_0225f538, data_ov004_0225f534;
extern unsigned short *func_0204f5e0(void *, unsigned int, unsigned int, int, int, unsigned char);
extern int func_02071298(void *, unsigned short *);
extern void func_020051b0(void *);
extern void __register_global_object(void *, void *destructor, void *);
extern int func_02053bc0(unsigned short *);
extern int func_0204f564(void *, unsigned short *, unsigned int, unsigned int, int, int, unsigned char);
}
// This scan is restricted to acre (0,0); x/y are its local tile coordinates.

static inline unsigned short *lookup(void *g, int x, int y)
{
    return func_0204f5e0(g, 0, 0, x, y, 0);
}
static inline bool is_range(unsigned short *p)
{
    bool result = false;
    if (*p >= 0x450c && *p <= 0x45db) {
        result = true;
    }
    return result;
}
static inline bool in_dex(unsigned short *p)
{
    bool result = false;
    if (func_02071298(data_021f38f8, p)) {
        result = true;
    }
    return result;
}
static inline void place(void *g, unsigned short *p, int x, int y)
{
    func_0204f564(g, p, 0, 0, x, y, 0);
}
extern "C" int func_ov004_0224522c(void)
{
    void *room = data_021c80bc;
    for (int y = 0; y < 16; ++y) {
        for (int x = 0; x < 16; ++x) {
            unsigned short *p = lookup(room, x, y);
            if (p && is_range(p) && !in_dex(p)) {
                if (!(data_ov004_0225f53c & 1)) {
                    data_ov004_0225f538 = 0x4a54;
                    __register_global_object(&data_ov004_0225f538, ((void *) &func_020051b0), data_ov004_0225f754);
                    data_ov004_0225f53c |= 1;
                }
                if (!(data_ov004_0225f540 & 1)) {
                    data_ov004_0225f534 = 0xfff1;
                    __register_global_object(&data_ov004_0225f534, ((void *) &func_020051b0), data_ov004_0225f634);
                    data_ov004_0225f540 |= 1;
                }
                int kind = func_02053bc0(p);
                unsigned short item = 0xfff1;
                if (!kind) {
                    item = data_ov004_0225f538;
                } else {
                    item = data_ov004_0225f534;
                }
                place(room, &item, x, y);
            }
        }
    }
    return 1;
}
