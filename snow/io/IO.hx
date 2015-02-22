package snow.io;

import snow.io.IOSystem;
import snow.types.Types;
import snow.io.typedarray.Uint8Array;
import snow.utils.promhx.Promise;

class IO {


    @:noCompletion public var lib : Snow;
    @:noCompletion public var platform : IOSystem;

        /** constructed internally, use `app.io` */
    @:allow(snow.Snow)
    function new( _lib:Snow ) {

        lib = _lib;

        platform = new IOSystem(this, lib);

        platform.init();

    } //new

        /** Call this to open a url in the default browser */
    public function url_open( _url:String ) {

        platform.url_open(_url);

    } //url_open

        /** Load bytes from the file path/url given.
            On web a request is sent for the data */
    public function data_load( _path:String, ?_options:IODataOptions ) : Promise<Uint8Array> {

        return platform.data_load( _path, _options );

    } //data_load


        /** Save bytes to the file path/url given.
            On platforms where this doesn't make sense (web) this will do nothing atm */
    public function data_save( _path:String, _data:Uint8Array, ?_options:IODataOptions ) : Bool {

        return platform.data_save( _path, _data, _options );

    } //data_save


        /** Return the full path that the application is located */
    public function app_path() : String {

        return Snow.core.app_path();

    } //app_path

        /** On platforms where this makes sense, get the application specific writeable data path.
            Uses the package from `SnowConfig`, passed through from flow projects or boot config. */
    public function app_path_prefs() : String {

        return Snow.core.app_path_prefs();

    } //app_path_prefs


//Internal

        /** Called by Snow when a system event happens. */
    @:allow(snow.Snow)
    function on_event( _event:SystemEvent ) {

        platform.on_event( _event );

    } //on_event

        /** Called by Snow, update any IO related processing */
    @:allow(snow.Snow)
    function update() {

        platform.process();

    } //update

        /** Called by Snow, cleans up IO */
    @:allow(snow.Snow)
    function destroy() {

        platform.destroy();

    } //destroy


} //IO
