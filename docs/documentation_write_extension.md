# 扩展程序开发文档


本应用支持使用标准C ABI的动态链接库的插件程序。

## 示例代码

* <del>完整项目的示例代码在`examples/`目录下。</del>

## API References

使用Doxygen可以生成本项目的API References。

## 插件的文件名命名方式

* 插件ID：插件ID是一个由字母和数字以及下划线组成的标识符。

文件名的构成为 `lib[插件ID].dylib`

例如，一个插件的ID为`test`，那么这个插件的文件名必须为`libtest.dylib`。

反之，对于一个文件名为`libtest.dylib`的插件，插件的ID即为`test`

注意：请不要使用类似`libtest.dylib.1`这种名称，同时`libtest.1.dylib`和`libtest.dylib`会被视为是两个插件。

## 创建项目

运行`tools/extension_bootstrap.sh`可创建插件的项目模板，其中包含必要的头文件和对应的C/C++实现。

使用下面的命令构建并生成一个插件。
```bash
cd tools
./extension_bootstrap.sh
cd extension_project  ## 项目目录
mkdir build
cd build
cmake ..  
make    ## 编译生成dylib
```

## 一个Hello World程序

```c++
#include "ac_common.h"
#include "ac_feature_core.h"
#include <iostream>

ACANE_EXTERN_C_START

ac_result_t ac_init() {
    LOGD("[external] initialized");
    return AC_OK;
}

ac_result_t ac_deinit() {
    LOGD("[external] de-initialized");
    return AC_OK;
}

ac_result_t ac_do_translate(ac_json_string_t input_json, ac_json_string_t* output_json) {
    LOGD("[external] do translate");
    *output_json = R"sample(
        {
           "code": 0,
           "message": "ok",
           "result": "hello world from native!"
         }
    )sample";
    return AC_OK;
}

ac_result_t ac_get_meta_info(ac_json_string_t* meta_json) {
    LOGD("[external] get meta info");
    *meta_json = R"sample(
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
})sample";
    return AC_OK;
}

ACANE_EXTERN_C_END
```

实现该程序的插件，只需要实现`ac_init`，`ac_deinit`，`ac_do_translate`和`ac_get_meta_info`即可。

## 需要实现的函数说明

### `ac_init` ：初始化插件

用于初始化插件，可在该函数中执行必要的操作。

### `ac_deinit` ：释放插件

用户释放插件所占用的资源

### `ac_do_translate` ：翻译

用户调用该函数进行翻译，传入的参数是一个JSON字符串，结构如下

```json
{
    "src": "zh",
    "dst": "en",
    "text": "你好，世界"
}
```

其中
* src为源语言，
* dst为目标语言，
* text是待翻译的文字。

该函数的返回值是包含翻译结果的字符串。所有的翻译都在这个函数进行。返回的字符串结构如下所示。

```json
{
    "code": 0,
    "message": "ok",
    "result": "hello, world"
}
```

其中
* code: 返回的代码，0表示正常返回，非0表示出现错误。
* message: 对错误详细的描述。
* result: 最终返回用于显示的结果。
仅会在code=0时，显示result中的内容。

**提示**

> 在解析传入的JSON或者返回JSON时，可以使用在API中提供的`TranslationRequest`类和`TranslationResult`类完成，具体的使用示例请参考`ac_ctrans.cpp`文件。

### `ac_get_meta_info` ：获取插件的元信息

该函数返回一个json字符串。

注意：该函数不应该用于储存配置信息，而仅用于提供程序所必要的元信息。

JSON格式如下所示

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

字段说明如下：

* name: `String`, 插件的名称 （可本地化）
* language_codes: `String数组`，支持的语言代码列表，用于翻译时传入src和dst（可本地化，本地化后的结果用于偏好设置的语言选项中）
* en_code: `String`, 英语的代码
* zh_code: `String`，简体中文的代码
* support_auto: `true`或`false`。是否支持自动选择源语言
* config: 用于配置在偏好设置界面配置参数。格式如下
```json
{
    "配置ID": { ... }
}
```
其中配置ID必须是英文和数字的组合，存储于数据库中作为配置项的主键。

支持以下3种配置项类型。

1. 文本输入

```json
{
    "name": "配置名称",
    "type": "text",
    "default": "Hello world"
}
```

 name为配置名称，显示在偏好设置中；type为配置类型；default为默认值。

 2. 列表选择

 ```json
{
    "name": "配置名称",
    "type": "list",
    "items": [ "hello", "world" ],
    "default": 0
}
 ```

 items为列表下拉框的内容。default为默认选择项的index。

 3. 复选框

 ```json
 {
    "name": "配置名称",
    "type": "bool",
    "default": false
}
 ```

 default为默认是否勾选，true为默认勾选，false为默认不勾选。

 ### `ac_report_db_location`：主程序向插件上报数据库位置和其他信息

这个函数会被调用3次

1. 第一次调用，实际类型为`const char*`类型，主程序向插件上报数据库位置，插件可使用获得的位置来获取数据库中的设置信息。

2. 第二次调用，实际类型为`const char*`类型，主程序向插件上报文档目录的位置

3. <del>第三次调用，实际类型为`struct MYSQL*`类型，传入了一个主程序使用的MySQL数据连接对象。（注意，请勿关闭这个数据库连接）</del>

## 配置项存储

使用使用程序自带的数据库存储设置信息。

通过`ac_report_db_location`上报的数据库位置，利用`ac_database.h`中的函数API打开sqlite数据库，利用`ac_settings.h`中的函数API存储和读取配置信息。

需要注意的是，`ac_settings.h`中的函数参数的ID为**本插件的ID**（在本文章最开始的地方有描述）。

可以使用`SettingsUtils.h`中提供的模板接口方便的获取配置信息。

------

&copy; 2020-2022 Acane

