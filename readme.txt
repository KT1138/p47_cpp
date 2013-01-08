○PARSEC47_CPPについて

	"PARSEC47"は長健太氏により作成されたWindows向けゲームであり、
	後日Evil Mr Henry氏によりLinux向け移植がなされました。

	"PARSEC47_C++"はHenry氏の移植を元に、D言語で書かれたコードを
	C++で再実装することにより作成したソフトウェアです。


○インストール方法

	p47_cpp.zipを適当なフォルダに展開するだけで大丈夫です。
	後はWindowsユーザの方は"p47_cpp.exe"をダブルクリック、
	Linuxユーザの方は端末から"p47_cpp"を実行してください。


○遊び方

	Linux版(p47_cpp)
	・移動								矢印キー
	・決定/ショット							[Z][左Ctrl]
	・モード切り替え/ロール・ロックショット		[X][左Alt][左Shift]
	・ポーズ								[P]

	Windows版(p47_cpp.exe)
	・移動								矢印キー
	・モード切り替え/ロール・ロックショット		[Z][左Ctrl]
	・決定/ショット							[X][左Alt][左Shift]
	・ポーズ								[P]

	「モード切り替え」はタイトル画面でのみ行うことができ、ロール・ロックショットのどちらを
	使用するかを選択します。

	「ロールショット」は前方に直進する、溜め撃ち式の強力なショットで、ゲーム中いつでも
	利用することができます。

	「ロックショット」は追尾式のショットで、キーを押している限り自動的に敵を補足し、発射されます。
	ただし中型以上の敵しか対象にならない点にご注意ください。

	なお自機は200,000点および500,000点ごとに一機増えます。
	

○PARSEC47とPARSEC47_C++の違い

	オリジナルのPARSEC47は、デフォルトでフルスクリーンモードで起動されますが、
	PARSEC47_C++のLinux向けバイナリは、ウインドウモードで起動するよう設定されています。
	これは環境によってはゲーム終了時に解像度に異常が生じる恐れがあるため、
	意図的にフルスクリーンモードを無効化しているためです。

	また敵の表示に関してもPARSEC47_C++はオリジナルに比べやや地味なものになっています。
	この点に関しては現在改良中であります。


○謝辞

	本ソフトウェアは長健太氏のPARSEC47をC++により再実装したものです。
	具体的に言うと、src/abagames/ディレクトリ以下のファイルを再実装の対象としました。
	クラス設計はPARSEC47のものを踏襲しています。
 	 PARSEC47
 	 http://www.asahi-net.or.jp/~cs8k-cyu/windows/p47.html

	Linux上でPARSEC47を稼働させるため、Evil Mr Henry氏による
	PARSEC47の移植を参考にしました。
 	 PARSEC47
 	 http://parsec47.sourceforge.net/

	BulletMLファイルのパースにlibBulletMLを利用しています。
 	 libBulletML
 	 http://shinh.skr.jp/bulletss/

	画面の出力にはSimple DirectMedia Layerを利用しています。
 	 Simple DirectMedia Layer
 	 http://www.libsdl.org/

	BGMとSEの出力にSDL_mixerとOgg Vorbis CODECを利用しています。
 	 SDL_mixer 1.2
 	 http://www.libsdl.org/projects/SDL_mixer/
 	 Vorbis.com
 	 http://www.vorbis.com/

	乱数発生器にMersenne Twisterを利用しています。
	元はmt.dというD言語のファイルだったものをC++で再実装し、
	mt.hおよびmt.cppとしました。
	変数構成や関数定義はmt.dを踏襲しています。
 	 http://www.math.keio.ac.jp/matumoto/emt.html


○ライセンス

	PARSEC47_CPPは修正BSDライセンスのもと配布します。


Copyright 2012 Koichi Yazawa. All rights reserved. 

Redistribution and use in source and binary forms, 
with or without modification, are permitted provided that 
the following conditions are met: 


 1. Redistributions of source code must retain the above copyright notice, 
    this list of conditions and the following disclaimer. 

 2. Redistributions in binary form must reproduce the above copyright notice, 
    this list of conditions and the following disclaimer in the documentation 
    and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, 
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL 
THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 


Copyright 2003 Kenta Cho. All rights reserved. 

Redistribution and use in source and binary forms, 
with or without modification, are permitted provided that 
the following conditions are met: 


 1. Redistributions of source code must retain the above copyright notice, 
    this list of conditions and the following disclaimer. 

 2. Redistributions in binary form must reproduce the above copyright notice, 
    this list of conditions and the following disclaimer in the documentation 
    and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, 
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL 
THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 



