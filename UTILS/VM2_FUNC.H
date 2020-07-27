#ifdef __cplusplus
extern "C" {
#endif

extern   struct shape ** far vm2_shapeload( void *shapefile );
extern   void     far vm2_shapefree( struct shape ** shapes);
extern   short    far vm2_shapecnt( struct shape **shapes );
extern   void     far vm2_flip_draw(struct shape *brush, short x, short y, short flip);
extern   void     far vm2_size_draw(struct shape *brush, short x, short y, short flip, short w, short h);
#define               vm2_draw(brush,x,y)    vm2_flip_draw(brush,x,y,0)

extern   short    far vm2_scrnload (void *scrn_file);

extern   void *   far bopen ( char huge * buffer );
extern   void     far bclose ( void );
extern   short    far numbits ( unsigned long l );

extern   ubyte    bgetbits ( short numbits );
extern   void     unpack_rectangle ( short x, short y, short w, short h );
extern   void     runpack_doit ( short x, short y, short w, short h );

extern short far vm2_load_scgs( void *shape_file );
extern void far vm2_free_scgs( void );
extern void far vm2_draw_scgs( short x, short y, short w, short h );
extern void far vm2_scroll_scgs( short dir, short val );

#ifdef __cplusplus
}
#endif

