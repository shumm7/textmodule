# textmodule
textmoduleは、AviUtlでワイド文字列を処理する関数などを複数追加するライブラリです。

# インストール / 使い方
詳細なドキュメントは https://shummg.work/archives/1157 を御覧ください。
1. exedit.aufと同じ場所に、textmodule.dll・libmecab.dll・textmoduleフォルダを配置する。
2. AviUtl側からrequire("textmodule")をする。
3. textmoduleという名前のテーブルがグローバルに登録されるので、使用したい関数を呼び出す。

# テーブルについて
+ textmodule： デバッグ用関数やAviUtlの関数を再現したもの。
+ textmodule.string： Lua標準のstringモジュールと類似の処理を、wchar_tで行った関数。
+ textmodule.tmstring： textmoduleオリジナルの文字列操作関数。
+ textmodule.tmstring.analyze： MeCabを使用した形態素解析によって文字列操作を行う関数。
+ textmodule.os： Lua標準のosモジュールと類似の処理を__time64_tで行った関数。
+ textmodule.utf8： Lua標準のutf8モジュールと類似の処理を、wchar_tで行った関数。
+ textmodule.color： 色情報の変換を行う関数。
+ textmodule.clipboard： クリップボード操作を行う関数。
+ textmodule.filesystem： ファイルパスを取得・操作する関数。
* textmodule.complex： 複素数クラスを取得・操作する関数。
* textmodule.quaternion： 四元数クラスを取得・操作する関数。
*
# ライセンス
textmoduleの著作権は、しゅう（ https://twitter.com/shulmj_ ）にあります。  

textmoduleはGNU Lesser General Public License 3.0（LGPL 3.0）の元で公開されています。  
これに従って、利用者は自由に本ライブラリを再配布したり改変したりすることができます。  
詳細はLICENCEをご確認ください。
