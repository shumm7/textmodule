# textmodule
textmoduleは、AviUtlでワイド文字列を処理する関数などを複数追加するライブラリです。

# インストール / 使い方
詳細なドキュメントは https://scrapbox.io/textmodule/ を御覧ください。
1. exedit.aufと同じ場所に、textmodule.dll・libmecab.dll・textmoduleフォルダを配置する。
2. AviUtl側からrequire("textmodule")をする。
3. textmoduleという名前のテーブルがグローバルに登録されるので、使用したい関数を呼び出す。

# Licence
textmoduleの著作権は、しゅう（ https://twitter.com/shulmj_ ）にあります。  

textmoduleはGNU Lesser General Public License 3.0（LGPL 3.0）の元で公開されています。  
これに従って、利用者は自由に本ライブラリを再配布したり改変したりすることができます。  
詳細はLICENCEをご確認ください。

## Dependencies
textmoduleは以下のオープンソースソフトウェアを使用しています。

### Lua
http://www.lua.org/  
Copyright (C) 1994-2003 Tecgraf, PUC-Rio. All rights reserved.  
This library is licensed under the MIT License.  

### MeCab
https://taku910.github.io/mecab/  
MeCab is copyrighted free software by Taku Kudo and Nippon Telegraph and Telephone Corporation.  
This library is licensed under the GNU Lesser General Public License Version 2.1.  

### nlohmann-json
https://github.com/nlohmann/json  
Copyright (C) 2013-2022 Niels Lohmann. All rights reserved.  
This library is licensed under the MIT License.  

### Eigen
https://eigen.tuxfamily.org/index.php  
Eigen is Free Software. It is licensed under the Mozilla Public License Version 2.0 (MPL2).  

### Portable C++ Hashing Library
https://github.com/stbrumme/hash-library  
Copyright (c) 2014,2015 Stephan Brumme. All rights reserved.  
This library is licensed under the zlib License.  

### C++ REST SDK
https://github.com/microsoft/cpprestsdk  
Copyright (C) Microsoft Corporation. All rights reserved.  
This library is licensed under the MIT License.  

### Fast C++ CSV Parser
https://github.com/ben-strasser/fast-cpp-csv-parser  
Copyright (c) 2015, ben-strasser. All rights reserved.  
This library is licensed under the BSD 3-Clause "New" or "Revised" License.  

### QR Code generator
https://github.com/nayuki/QR-Code-generator  
Copyright (c) 2022, Project Nayuki. All rights reserved.  
This library is licensed under the MIT License.  
