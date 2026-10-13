/* func_02003038 @ 0x02003038, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02003038(void *param1);
extern void DC_FlushRange(void *param1, int param2);
extern void GX_LoadOBJ(void *param1, int param2, int param3);
extern void GXS_LoadOBJ(void *param1, int param2, int param3);

void func_02003038(void *param1)
{
    void *r4 = param1;
    DC_FlushRange(*(void **) ((char *) r4 + 0x4c), 0x1000);
    GX_LoadOBJ(*(void **) ((char *) r4 + 0x4c), 0, 0x1000);
    GXS_LoadOBJ(*(void **) ((char *) r4 + 0x4c), 0, 0x1000);
}
