/*
 *    Copyright (C) 2022  Acane
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * */

//
// Created by Acane on 2022/2/9.
//

#ifndef EXTENSION_TRANSLATEUTILS_H
#define EXTENSION_TRANSLATEUTILS_H

#include <string>

class TranslateRequest {
public:
    std::string dst;
    std::string src;
    std::string text;

    TranslateRequest& parse(const char* json);
};

class TranslateResult {
public:
    int code = 0;
    std::string message;
    std::string result;

    TranslateResult(int code, const std::string &message, const std::string &result);

    static TranslateResult error(int code, const std::string &message);
    static TranslateResult create(const std::string &result);

    std::string encodeJSON();
};

#endif //EXTENSION_TRANSLATEUTILS_H
