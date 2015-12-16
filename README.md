# MyLibrary
it's just for me. I don't care and help if you use this.

If you want README written in English, make pull request.

# MyLibrary について

自分用の共有ライブラリ，ROOT の CINT 用マクロ集。
基本的に，

* すべてのライブラリで，使用するしないにかかわらず root-config をコンパイル時に使用
* CINT のマクロはソースファイル .cc を読み込んで使う。

としている。

## [関数・クラスの説明][doxygen]

## 詳しい説明

* bin
* include
* lib
* src

### bin
 
スクリプトの置き場。
なぜか，Makeheaderfile.sh はここに置いていない。
あとでなおす。


### src/*.cc

ソースファイル。
基本的に，1 ファイル 1 ライブラリとする。
たいていは，大きな枠組み+Operation.cc という名前になっている。
拡張子を .hh に置き換えたものが対応するヘッダーファイル。

### include/*.hh

ヘッダーファイル。

* ソースファイルに対応するもの
* 一般的なヘッダーを読み込むもの
* MyLibrary.hh

がある。

#### include/MyLibrary.hh

CINT でマクロとして使うときに，インクルードするファイル。
ソースファイルの追加や削除をするたびに作りなおす必要がある。
作り方は

	cd ${MyLibrary}
	./MakeHeaderFile.sh

または

	cd ${MyLibrary}/src
	make MyLibrary.hh

でできる。
make all でもできる。

### lib/*

共有ファイル置き場・

## インストール

github からダウンロードし，MyLibrary ディレクトリで

	cd src
	make -j all

でコンパイルする。
linux では "lib*.so"，mac では "lib*.dylib" ファイルができる（mac ではよくわからないディレクトリもできる。これは使わない）。

共有ライブラリのコンパイルと同時に，MyLibrary.hh も作成し，MyLibrary/include に置かれる。
これは CINT で使うときにインクルードするもの。
使い方は後で紹介する。

インストールは

	make install

とやると，MyLibrary/lib に共有ライブラリがインストールされる。

また，コンパイル時にヘッダファイルや共有ライブラリの場所を指定するためのスクリプトも作らなければならない。

	cd ${MyLibrary}/bin
	./install.sh

とすると， ~/bin に MyLibrary-config ができる。
~/bin を PATH に通しておくべし。

	export PATH=${HOME}/bin:${PATH}

※場所は install.sh を編集すれば変更できる。

共有ライブラリを使うときに，ファイルを探すディレクトリ集の中に，MyLibrary/lib を追加する。
例えば .bashrc に

	export LD_LIBRARY_PATH=${HOME}/local/MyLibrary/lib:${LD_LIBRARY_PATH}
	export CPATH=${HOME}/local/MyLibrary/include:${CPATH}

と書くべし。

## 実践編

### CINT のマクロで使う

インクルードの前に

	\#define __CINT__

をする。

インクルードは

	#include "${path_to_mylibrary}/lib/MyLibrary.hh"

のみで OK。
ここで，${path\_to\_mylibrary} は MyLibrary ディレクトリへのパスにしなければならない。
例えば "/home/john/local/MyLibrary" 。

### 共有ライブラリを使う

コンパイル時に，

	`MyLibrary-config`

を入れれば OK のはず。

[doxygen]: https://nukazuka.github.io/MyLibrary/index.html
