# Extension Development Documentation

This application supports dynamical library with standard c ABI as extensions. 

This repository stores header files and dynamical libraries needed for developing plugins.

## Sample Codes

* The example code is stored under `examples/` directory.

## API References

Use Doxygen to generate the API References of this project.

## Name the Extension

* Extension ID: The extension ID is an identifier consisting of letters and numbers and underscores.

The filename is formed as `lib[extension_id].dylib`

For example, if a plugin has an ID of `test`, then the plugin's filename must be `libtest.dylib`.

Conversely, for a plugin whose filename is `libtest.dylib`, the ID of the plugin is `test`.

Note: Please do not use names like `libtest.dylib.1`. 
Meanwhile, `libtest.1.dylib` and `libtest.dylib` will be considered as two plugins.

## Create Project

Copy the files in the example directory and change the `plugin_main.cpp` in the src directory to your own plugin code.

In the project directory in example, use the following command to build the plugin.

```bash
mkdir build
cd build
cmake ..  
make    ## build the plugin
```

In order to realize JSON parsing and network access more conveniently, you can also manually add boost library or json parsing library, etc., but note that if you add other dylib dynamic library files, please compile x86_64 and arm64 versions at the same time, and use the lipo command to merge them into an univeral dylib, otherwise running this plugin on the universal platform will cause the main program to crash or fail to load the plugin.

The merge command using `lipo` is as follows

```bash
$ lipo -create -output libsample.dylib libsample.dylib.arm64 libsample.dylib.x86_64 
```

## Functions to be Implemented

To implement the plugin of this program, only need to implement `ac_init`, `ac_deinit`, `ac_do_translate` and `ac_get_meta_info`. 

Must contain the functions above listed. And you cannot change function parameter types, function names, and return value types. 
And if you are using C++, be sure to use `extern "C"` to modify these functions to export the function names of the C language ABI.

### `ac_init` : Initialize the plugin

Used to initialize the plugin, the necessary operations can be performed in this function.

### `ac_deinit` : Release resources of the plugin

The user releases the resources occupied by the plugin.

### `ac_do_translate`: Translate

Call this function to translate, the incoming parameter is a JSON string, the structure is as follows.

```json
{
    "src": "zh",
    "dst": "en",
    "text": "你好，世界"
}
```

Where
* `src` denotes to source language，
* `dst` denotes to destination language,
* `text` denotes to words to translate.

The return value of this function is a string containing the translation result. 
All translations are done in this function. The returned string structure is shown below.

```json
{
    "code": 0,
    "message": "ok",
    "result": "hello, world"
}
```

Where
* code: The return code, 0 denotes to return normally, non-zero denotes to return with errors.
* message: Detailed description of the error.
* result: The translation result.

The content in result will only be displayed when `code=0`.

**Note**

> When parsing incoming JSON or returning JSON, you can use the `TranslationRequest` class and `TranslationResult` class provided in the API to complete. For specific usage examples, please refer to the `ac_ctrans.cpp` file.

### `ac_get_meta_info` : Get the meta information of the plugin

The function returns a json string.

Note: This function should not be used to store configuration information, but only to provide meta-information necessary for the program.

The JSON format is as follows

```json
{
    "name": "Test Service",
    "language_codes": ["zh", "en", "jp"],
    "en_code": "en",
    "zh_code": "zh",
    "i18n": {
        "zh": {
            "en": "Chinese",
            "zh": "中文"
        },
        "en": {
            "en": "English",
            "zh": "英语"
        },
        "jp": "Japanese",
        "Use advanced feature": { "zh": "你好，世界" },
        "Domains": { "zh": "区域" },
        "Global domain": { "zh": "全部区域" }
    },
    "support_auto": false,
    "config": {
        "api_keys": {
            "name": "API Key",
            "type": "text",
            "default": "Hello world"
        },
        "api_domains": {
            "name": "Domains",
            "type": "list",
            "items": [ "Global domain", "Local domain" ]
        },
        "api_check": {
            "name": "Use advanced feature",
            "type": "bool",
            "default": false
        }
    }
}

```

Field descriptions are as follows:

* name: `String`, the name of the plugin (localizable)
* language_codes: `String Array`, a list of supported language codes, which are used to pass in src and dst during translation (localization is possible, and the localized result is used in the language option of the preference setting)
* en_code: `String`, code of English
* zh_code: `String`, code of Simpified Chinese
* support_auto: `true` or `false`. Whether to support automatic selection of source language
* config: Used to configure configuration parameters in the preferences interface. The format is as follows
```json
{
    "Configuration ID": { ... }
}
```

The configuration ID must be a combination of English and numbers, which is stored in the database as the primary key of the configuration item.

The following three configuration item types are supported.

1. Text input

```json
{
    "name": "Configuration Name",
    "type": "text",
    "default": "Hello world"
}
```

name is the configuration name, displayed as the title before the input control; type is the configuration type; default is the default value.

 2. List

 ```json
{
    "name": "Configuration Name",
    "type": "list",
    "items": [ "hello", "world" ],
    "default": 0
}
 ```

`items` is the content of the list drop-down box. `default` is the index of the default selection

 3. Checkbox

 ```json
 {
    "name": "Configuration Name",
    "type": "bool",
    "default": false
}
 ```

`default` is whether it is checked by default, `true` is checked by default, and `false` is not checked by default.

 ### `ac_report_db_location`: The main program reports the database location and other information to the plugin

This function will be called 3 times

1. The first call, the actual type is `const char*`, the main program reports the database location to the plug-in, and the plug-in can use the obtained location to obtain the setting information in the database.

2. The second call, the actual type is `const char*`, the main program reports the location of the document directory to the plugin

3. <del>The third call, the actual type is `struct MYSQL*`, and a MySQL data connection object used by the main program is passed in. (Note, do not close this database connection)</del>

## Configuration item storage

Use the database that comes with the program to store setup information.

Through the database location reported by `ac_report_db_location`, use the function API in `ac_database.h` to open the sqlite database, and use the function API in `ac_settings.h` to store and read configuration information.

It should be noted that the ID of the function parameter in `ac_settings.h` is **the ID of this plugin** (described at the beginning of this article).

Configuration information can be easily obtained using the template interface provided in `SettingsUtils.h`.

------

&copy; 2020-2022 Acane

