
[![Logo](../../../images/logo.png)](../../../api/index.html)

---



<h1>Assets</h1>
<small>`snow.assets.Assets`</small>

The asset system class gives you access to fetching and manipulating assets,
    caching/uncaching assets, and handles loading files and data cross platform

---

`class`

---

&nbsp;
&nbsp;



<h3>Members</h3> <hr/><span class="member apipage">
                <a name="list"><a class="lift" href="#list">list</a></a><div class="clear"></div><code class="signature apipage">list : [Map](#)&lt;[String](#), [snow.types.AssetInfo](#)&gt;</code><br/></span>
            <span class="small_desc_flat">The list of assets in the system, added at startup by the `App` class, in the `get_asset_list` function</span><span class="member apipage">
                <a name="assets_root"><a class="lift" href="#assets_root">assets\_root</a></a><div class="clear"></div><code class="signature apipage">assets\_root : [String](#)</code><br/></span>
            <span class="small_desc_flat">If the assets are not relative to the runtime root path, this value can adjust all asset paths. This is automatically handled and exists to allow control.</span><span class="member apipage">
                <a name="manifest_path"><a class="lift" href="#manifest_path">manifest\_path</a></a><div class="clear"></div><code class="signature apipage">manifest\_path : [String](#)</code><br/></span>
            <span class="small_desc_flat">The manifest file to parse for the asset list. By default, this is set to `manifest` from the build tools but the `App` class can have a custom `get_asset_list` handler use this value.</span>





<h3>Methods</h3> <hr/><span class="method apipage">
            <a name="add"><a class="lift" href="#add">add</a></a> <div class="clear"></div><code class="signature apipage">add(\_list:[Array](#)&lt;[snow.types.AssetInfo](#)&gt;<span></span>) : [Void](#)</code><br/><span class="small_desc_flat">Add an asset list to the system</span>
        </span>
    <span class="method apipage">
            <a name="get"><a class="lift" href="#get">get</a></a> <div class="clear"></div><code class="signature apipage">get(\_id:[String](#)<span></span>) : [snow.types.AssetInfo](#)</code><br/><span class="small_desc_flat">Get an asset from the system</span>
        </span>
    <span class="method apipage">
            <a name="exists"><a class="lift" href="#exists">exists</a></a> <div class="clear"></div><code class="signature apipage">exists(\_id:[String](#)<span></span>) : [Bool](#)</code><br/><span class="small_desc_flat">Check if an asset exists in the system</span>
        </span>
    <span class="method apipage">
            <a name="path"><a class="lift" href="#path">path</a></a> <div class="clear"></div><code class="signature apipage">path(\_id:[String](#)<span></span>) : [String](#)</code><br/><span class="small_desc_flat">Get the asset path for an asset, adjusted by platform, root etc.</span>
        </span>
    <span class="method apipage">
            <a name="get_bytes"><a class="lift" href="#get_bytes">get\_bytes</a></a> <div class="clear"></div><code class="signature apipage">get\_bytes(\_id:[String](#)<span></span>) : [snow.types.AssetBytes](#)</code><br/><span class="small_desc_flat">Get an asset as a `ByteArray`, used for binary assets</span>
        </span>
    <span class="method apipage">
            <a name="get_text"><a class="lift" href="#get_text">get\_text</a></a> <div class="clear"></div><code class="signature apipage">get\_text(\_id:[String](#)<span></span>) : [snow.types.AssetText](#)</code><br/><span class="small_desc_flat">Get an asset as a `String`, used for text based assets</span>
        </span>
    <span class="method apipage">
            <a name="get_image"><a class="lift" href="#get_image">get\_image</a></a> <div class="clear"></div><code class="signature apipage">get\_image(\_id:[String](#)<span></span>, options:[snow.types.AssetImageOptions](#)<span>=null</span>) : [snow.types.AssetImage](#)</code><br/><span class="small_desc_flat">Get an asset as a `AssetImage`, used for image files</span>
        </span>
    <span class="method apipage">
            <a name="get_audio"><a class="lift" href="#get_audio">get\_audio</a></a> <div class="clear"></div><code class="signature apipage">get\_audio(\_id:[String](#)<span></span>, options:[snow.types.AssetAudioOptions](#)<span>=null</span>) : [snow.types.AssetAudio](#)</code><br/><span class="small_desc_flat">Get an asset as a `AssetAudio`, used for audio files</span>
        </span>
    <span class="method apipage">
            <a name="new"><a class="lift" href="#new">new</a></a> <div class="clear"></div><code class="signature apipage">new(\_lib:[snow.Snow](#)<span></span>) : [Void](#)</code><br/><span class="small_desc_flat"></span>
        </span>
    





---

&nbsp;
&nbsp;
&nbsp;
&nbsp;