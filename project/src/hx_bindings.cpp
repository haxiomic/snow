#ifndef STATIC_LINK
#define IMPLEMENT_API
#endif

#if defined(HX_WINDOWS) || defined(HX_MACOS) || defined(HX_LINUX)
// Include neko glue....
#define NEKO_COMPATIBLE
#endif

#include <hx/CFFI.h>

#ifdef ANDROID
#include <android/log.h>
#endif

#include "hx_bindings.h"

#include "lumen_core.h"
#include "lumen_window.h"
#include "lumen_input.h"

#include "common/ByteArray.h"
#include "libs/lzma/lzma.h"

namespace lumen {

        //has id's etc been inited?
    static int global_lumen_init = false;
        //a "kind" type for native wrapped objects
    vkind global_lumen_object_kind;
        //core event haxe callback handler
        //a core system event handler implementation (defined in hx_bindings.h)
    AutoGCRoot *system_event_handler = 0;

    extern "C" void lumen_entry_point() {

        if (global_lumen_init){
            return;
        }

       global_lumen_init = true;

       lumen_init_ids();

    } DEFINE_ENTRY_POINT(lumen_entry_point)




// core bindings




extern double timestamp();


    value lumen_init( value _on_event ) {

            //fetch the callback for system events
        system_event_handler = new AutoGCRoot(_on_event);

            //now init the core
        lumen_core_init();

        return alloc_null();
    
    } DEFINE_PRIM(lumen_init, 1);


    value lumen_shutdown() {

            //now shutdown the core
        lumen_core_shutdown();

        return alloc_null();
    
    } DEFINE_PRIM(lumen_shutdown, 0);


    value lumen_timestamp() {

        return alloc_float( lumen::timestamp() );

    } DEFINE_PRIM(lumen_timestamp, 0);





//application helpers





    value lumen_app_path() {

        return alloc_string( core_app_path() );
    
    } DEFINE_PRIM(lumen_app_path, 0);


    value lumen_pref_path(value _org, value _app) {

        return alloc_string( core_pref_path( val_string(_org), val_string(_app) ) );

    } DEFINE_PRIM(lumen_pref_path, 2);





//render bindings


extern int render_enable_vsync(bool enable);

    value lumen_render_enable_vsync( value _enable ) {

        int result = render_enable_vsync( val_bool(_enable) );

        return alloc_int( result );

    } DEFINE_PRIM(lumen_render_enable_vsync, 1);




//display bindings



extern int          desktop_get_display_count();
extern int          desktop_get_display_mode_count(int display);
extern value        desktop_get_display_native_mode(int display);
extern value        desktop_get_display_current_mode(int display);
extern value        desktop_get_display_mode(int display, int mode_index);
extern value        desktop_get_display_bounds(int display);
extern const char*  desktop_get_display_name(int display);


    value lumen_desktop_get_display_count() {

        return alloc_int(desktop_get_display_count());

    } DEFINE_PRIM(lumen_desktop_get_display_count, 0);
    

    value lumen_desktop_get_display_mode_count(value _display) {

        return alloc_int(desktop_get_display_mode_count( val_int(_display) ));

    } DEFINE_PRIM(lumen_desktop_get_display_mode_count, 1);


    value lumen_desktop_get_display_native_mode(value _display) {

        return desktop_get_display_native_mode( val_int(_display) );

    } DEFINE_PRIM(lumen_desktop_get_display_native_mode, 1);


    value lumen_desktop_get_display_current_mode(value _display) {

        return desktop_get_display_current_mode( val_int(_display) );

    } DEFINE_PRIM(lumen_desktop_get_display_current_mode, 1);


    value lumen_desktop_get_display_mode(value _display, value _mode_index) {

        return desktop_get_display_mode( val_int(_display), val_int(_mode_index) );

    } DEFINE_PRIM(lumen_desktop_get_display_mode, 2);


    value lumen_desktop_get_display_bounds(value _display) {

        return desktop_get_display_bounds( val_int(_display) );

    } DEFINE_PRIM(lumen_desktop_get_display_bounds, 1);


    value lumen_desktop_get_display_name(value _display) {

        return alloc_string( desktop_get_display_name( val_int(_display) ));

    } DEFINE_PRIM(lumen_desktop_get_display_name, 1);





// window bindings




extern void window_show_cursor(bool enable);



    value lumen_window_create( value _in_config, value _on_created ) {

            //fetch the callback for when it's done opening the window
        AutoGCRoot *on_created = new AutoGCRoot( _on_created );
            
            //fetch window config from the haxe side
        window_config config = window_config_from_hx(_in_config);
            //create the actual window
        create_window( config, on_created );

        return alloc_null();
    
    } DEFINE_PRIM(lumen_window_create, 2);


    value lumen_window_update( value _window ) {

        LumenWindow* window = NULL;

        if( Object_from_hx(_window, window) ) {

            window->update();

        } //fetch window

        return alloc_null();

    } DEFINE_PRIM(lumen_window_update, 1);


    value lumen_window_render( value _window ) {

        LumenWindow* window = NULL;

        if( Object_from_hx(_window, window) ) {

            window->render();

        } //fetch window

        return alloc_null();

    } DEFINE_PRIM(lumen_window_render, 1);


    value lumen_window_swap( value _window ) {

        LumenWindow* window = NULL;

        if( Object_from_hx(_window, window) ) {

            window->swap();

        } //fetch window

        return alloc_null();

    } DEFINE_PRIM(lumen_window_swap, 1);


    value lumen_window_simple_message( value _window, value _message, value _title ) {

        LumenWindow* window = NULL;

        if( Object_from_hx(_window, window) ) {

            window->simple_message( val_string(_message), val_string(_title) );

        } //fetch window

        return alloc_null();

    } DEFINE_PRIM(lumen_window_simple_message, 3);


    value lumen_window_set_size(value _window, value _x, value _y) {

        LumenWindow* window = NULL;

        if( Object_from_hx(_window, window) ) {

            window->set_size( val_int(_x), val_int(_y) );

        } //fetch window

        return alloc_null();

    } DEFINE_PRIM(lumen_window_set_size, 3);


    value lumen_window_set_position(value _window, value _x, value _y) {

        LumenWindow* window = NULL;

        if( Object_from_hx(_window, window) ) {

            window->set_position( val_int(_x), val_int(_y) );

        } //fetch window

        return alloc_null();

    } DEFINE_PRIM(lumen_window_set_position, 3);


    value lumen_window_set_title(value _window, value _title) {

        LumenWindow* window = NULL;

        if( Object_from_hx(_window, window) ) {

            window->set_title( val_string(_title) );

        } //fetch window

        return alloc_null();

    } DEFINE_PRIM(lumen_window_set_title, 2);


    value lumen_window_set_max_size(value _window, value _x, value _y) {
        
        LumenWindow* window = NULL;

        if( Object_from_hx(_window, window) ) {

            window->set_max_size( val_int(_x), val_int(_y) );

        } //fetch window

        return alloc_null();

    } DEFINE_PRIM(lumen_window_set_max_size, 3);


    value lumen_window_set_min_size(value _window, value _x, value _y) {

        LumenWindow* window = NULL;

        if( Object_from_hx(_window, window) ) {

            window->set_min_size( val_int(_x), val_int(_y) );

        } //fetch window

        return alloc_null();

    } DEFINE_PRIM(lumen_window_set_min_size, 3);


    value lumen_window_grab(value _window, value _enable) {
        
        LumenWindow* window = NULL;

        if( Object_from_hx(_window, window) ) {

            window->grab( val_bool(_enable) );

        } //fetch window

        return alloc_null();

    } DEFINE_PRIM(lumen_window_grab, 2);


    value lumen_window_fullscreen(value _window, value _enable, value _flag) {

        LumenWindow* window = NULL;

        if( Object_from_hx(_window, window) ) {

            window->fullscreen( val_bool(_enable), val_int(_flag) );

        } //fetch window

        return alloc_null();

    } DEFINE_PRIM(lumen_window_fullscreen, 3);


    value lumen_window_bordered(value _window, value _enable) {

        LumenWindow* window = NULL;

        if( Object_from_hx(_window, window) ) {

            window->bordered( val_bool(_enable) );

        } //fetch window

        return alloc_null();

    } DEFINE_PRIM(lumen_window_bordered, 2);


    value lumen_window_show_cursor(value _enable) {

        window_show_cursor( val_bool(_enable) );

        return alloc_null();

    } DEFINE_PRIM(lumen_window_show_cursor, 1);

// input bindings





    value lumen_gamepad_open( value _id ) {

        input_gamepad_open(val_int(_id));

        return alloc_null();

    } DEFINE_PRIM(lumen_gamepad_open, 1)

    value lumen_gamepad_close( value _id ) {

        input_gamepad_close(val_int(_id));

        return alloc_null();

    } DEFINE_PRIM(lumen_gamepad_close, 1)






// audio loading






extern bool audio_load_ogg_bytes( QuickVec<unsigned char> &out_buffer, const char* _id, 
                int* channels, long* rate, long* bitrate_upper, long* bitrate, 
                long* bitrate_lower, long* bitrate_window,  int *bits_per_sample );

extern bool audio_load_wav_bytes( QuickVec<unsigned char> &out_buffer, const char *_id,  int *channels, int* rate, int *bitrate, int *bits_per_sample);

    value lumen_audio_load_ogg_bytes( value _id ) {

        QuickVec<unsigned char> buffer;
        int ch; 
        long rate;        
        long bitrate;
        int bits_per_sample;

        long br_u; long br_w; long br_l;

        bool success = audio_load_ogg_bytes( buffer, val_string(_id), &ch, &rate, &br_u, &bitrate, &br_l, &br_w, &bits_per_sample );

        if(!success) {
            return alloc_null();
        } //!success

        value _object = alloc_empty_object();

            alloc_field( _object, id_id, _id );
            alloc_field( _object, id_channels, alloc_int(ch) );
            alloc_field( _object, id_rate, alloc_int(rate) );
            alloc_field( _object, id_format, alloc_int(1) ); //1 here is ogg
            alloc_field( _object, id_bitrate, alloc_int(bitrate) );
            alloc_field( _object, id_bits_per_sample, alloc_int(bits_per_sample) );
            alloc_field( _object, id_data, ByteArray(buffer).mValue );

        return _object;

    } DEFINE_PRIM(lumen_audio_load_ogg_bytes, 1);


    value lumen_audio_load_wav_bytes( value _id ) {

        QuickVec<unsigned char> buffer;
        int ch; 
        int rate;
        int bitrate;
        int bits_per_sample;

        bool success = audio_load_wav_bytes( buffer, val_string(_id), &ch, &rate, &bitrate, &bits_per_sample );
        
        if(!success) {
            return alloc_null();
        } //!success

        value _object = alloc_empty_object();

            alloc_field( _object, id_id, _id );
            alloc_field( _object, id_channels, alloc_int(ch) );
            alloc_field( _object, id_rate, alloc_int(rate) );
            alloc_field( _object, id_format, alloc_int(0) ); //0 here is wav
            alloc_field( _object, id_bitrate, alloc_int(bitrate) );
            alloc_field( _object, id_bits_per_sample, alloc_int(bits_per_sample) );
            alloc_field( _object, id_data, ByteArray(buffer).mValue );

        return _object;

    } DEFINE_PRIM(lumen_audio_load_wav_bytes, 1);





// image loading





extern void image_load_bytes( QuickVec<unsigned char> &out_buffer, const char* _id, int* w, int* h, int* bpp, int* bpp_source, int req_bpp );

    value lumen_image_load_bytes( value _id, value _req_bpp ) {

        QuickVec<unsigned char> buffer;

        int w = 0, h = 0, bpp = 0, bpp_source = 0;
        int req_bpp = val_int(_req_bpp);

        image_load_bytes( buffer, val_string(_id), &w, &h, &bpp, &bpp_source, req_bpp );

        value _object = alloc_empty_object();

            alloc_field( _object, id_id, _id );
            alloc_field( _object, id_width, alloc_int(w) );
            alloc_field( _object, id_height, alloc_int(h) );
            alloc_field( _object, id_bpp, alloc_int(bpp) );
            alloc_field( _object, id_bpp_source, alloc_int(bpp_source) );
            alloc_field( _object, id_data, ByteArray(buffer).mValue );

        return _object;

    } DEFINE_PRIM(lumen_image_load_bytes, 2);





//LZMA bindings





    value lumen_lzma_encode(value input_value) {

       buffer input_buffer = val_to_buffer(input_value);
       buffer output_buffer = alloc_buffer_len(0);

       Lzma::Encode(input_buffer, output_buffer);

       return buffer_val(output_buffer);

    } DEFINE_PRIM(lumen_lzma_encode,1);

    value lumen_lzma_decode(value input_value) {

       buffer input_buffer = val_to_buffer(input_value);
       buffer output_buffer = alloc_buffer_len(0);

       Lzma::Decode(input_buffer, output_buffer);

       return buffer_val(output_buffer);

    } DEFINE_PRIM(lumen_lzma_decode,1);





//ByteArray bindings





    value lumen_byte_array_overwrite_file(value inFilename, value inBytes) {
            // file is created if it doesn't exist,
            // if it exists, it is truncated to zero
        FILE *file = OpenOverwrite(val_os_string(inFilename));
        if (!file) {

            #ifdef ANDROID
                // [todo]
            #endif

            return alloc_null();
       }

        ByteArray array(inBytes);

            // The function fwrite() writes nitems objects, each size bytes long, to the
            // stream pointed to by stream, obtaining them from the location given by
            // ptr.  fwrite(const void *restrict ptr, size_t size, size_t nitems, FILE *restrict stream);
        fwrite( array.Bytes() , 1, array.Size() , file);

        fclose(file);

        return alloc_null();

    } DEFINE_PRIM(lumen_byte_array_overwrite_file, 2);


    value lumen_byte_array_read_file(value inFilename) {

        ByteArray result = ByteArray::FromFile(val_os_string(inFilename));
       
        return result.mValue;

    } DEFINE_PRIM(lumen_byte_array_read_file,1);


    value lumen_byte_array_get_native_pointer(value inByteArray) {

        ByteArray bytes (inByteArray);
        
        if (!val_is_null (bytes.mValue)) {
            return alloc_int((intptr_t)bytes.Bytes ());
        }

        return alloc_null();

    } DEFINE_PRIM(lumen_byte_array_get_native_pointer,1);




//Native glue stuff


    int id_id;
    int id_type;
    int id_event;
    int id_x;
    int id_y;
    int id_width;
    int id_height;
    int id_text;
    int id_length;
    int id_data;

    int id_window;
    int id_window_id;
    int id_timestamp;    
    int id_data1;
    int id_data2;

    int id_refresh_rate;

    int id_input;
    int id_start;
    int id_state;
    int id_repeat;
    int id_mod;
    int id_sym;
    int id_keysym;
    int id_scancode;
    int id_which;
    int id_xrel;
    int id_yrel;
    int id_button;
    int id_dx;
    int id_dy;
    int id_finger_id;
    int id_touch_id;
    int id_pressure;
    int id_axis;
    int id_value;
    int id_ball;
    int id_hat;

    int id_bpp;
    int id_bpp_source;

    int id_format;
    int id_channels;
    int id_rate;
    int id_bitrate;
    int id_bits_per_sample;
    int id_bitrate_upper;
    int id_bitrate_nominal;
    int id_bitrate_lower;
    int id_bitrate_window;

    int id_title;
    int id_fullscreen;
    int id_resizable;
    int id_borderless;
    int id_antialiasing;
    int id_depth_buffer;
    int id_stencil_buffer;
    int id_vsync;
    int id_fps;



    #ifdef STATIC_LINK
        extern "C" int lumen_opengl_sdl2_register_prims();
        extern "C" int lumen_audio_openal_register_prims();
    #endif //STATIC_LINK

    extern "C" int lumen_register_prims() {

          lumen_entry_point();

            #ifdef STATIC_LINK
                lumen_opengl_sdl2_register_prims();
                lumen_audio_openal_register_prims();
            #endif
       
        return 0;

    } //lumen_register_prims



} //namespace lumen

