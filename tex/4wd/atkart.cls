%% 視覚情報処理研究室卒業論文クラスファイル
%% Ver.1.0 <2021-04-16>

% パッケージ
\RequirePackage{expl3,xparse,l3keys2e}

% クラス宣言
\NeedsTeXFormat{LaTeX2e}
\ProvidesExplPackage {atkart} {2021/04/07} {1.0}
  {Document class for the thesis of Visual Information Processing Research Lab}

% (u)pTeX 用パッチ
\sys_if_engine_ptex:T { \RequirePackage { plautopatch } }
\sys_if_engine_uptex:T { \RequirePackage { plautopatch } }

% クラスオプション
\bool_new:N \g_atk_ac_bool
\bool_new:N \g_atk_nogutter_bool
\bool_new:N \g_atk_oneside_bool
\str_new:N \g_atk_english_str
\bool_new:N \g_atk_english_titlepage_bool
\bool_new:N \g_atk_english_caption_bool

\clist_new:N \g__atk_options_clist
\clist_new:N \g__atk_disallowed_options_clist
\seq_new:N \g__atk_disallowed_options_seq

% jlreq に渡す
\clist_gset:Nn \g__atk_disallowed_options_clist
  {
    article, report, book, paper, fontsize, jafontsize, jafontscale,
    line_length, number_of_lines, head_space, foot_space, gutter, fore_edge,
    fore-edge, headfoot_verticalposition, headfoot_sidemargin, column_gap,
    baselineskip, linegap, hanging_punctuation, narrow_kanjiskip,
    sidenote_length, use_reverse_pagination, landscape, tate, oneside, twoside,
    oneclumn, twocolumn, titlepage, notitlepage, openright, openany
  }
\clist_map_inline:Nn \g__atk_disallowed_options_clist
  {
    \seq_gput_right:Nx \g__atk_disallowed_options_seq { \tl_to_str:n { #1 } }
  }
\cs_new:Nn \__atk_process_class_option:
  {
    \cs_if_exist:NF \l_keys_key_str
      { \cs_set_eq:NN \l_keys_key_str \l_keys_key_tl }
    \seq_if_in:NoTF \g__atk_disallowed_options_seq { \l_keys_key_str }
      { \msg_warning:nnx { atkart } { disallowed-option } { \l_keys_key_str } }
      { \clist_gput_right:No \g__atk_options_clist { \CurrentOption } }
  }

% オプション実行
\keys_define:nn { atkart / option }
  {
    ac .bool_gset:N = \g_atk_ac_bool,
    ac .default:n = true,
    nogutter .bool_gset:N = \g_atk_nogutter_bool,
    nogutter .default:n = true,
    oneside .bool_gset:N = \g_atk_oneside_bool,
    oneside .default:n = true,
    english .code:n = { \str_gset:Nn \g_atk_english_str { #1 } },
    english .initial:n = no,
    english .value_required:n = true,
    unknown .code:n = \__atk_process_class_option:
  }
\ProcessKeysOptions { atkart / option }
\PassOptionsToClass { \g__atk_options_clist } { jlreq }

\str_case:VnF \g_atk_english_str
  {
    { no } {}
    { caption }
    {
      \bool_gset:Nn \g_atk_english_caption_bool { 1 }
    }
    { titlepage }
    {
      \bool_gset:Nn \g_atk_english_titlepage_bool { 1 }
    }
    { all }
    {
      \bool_gset:Nn \g_atk_english_titlepage_bool { 1 }
      \bool_gset:Nn \g_atk_english_caption_bool { 1 }
    }
  }
  {
    \ClassError { atkart } { Unknown~ english~ setting }
      {
        Invalid~ value~ for~ the~ 'english'~ option:~
        '\g_atk_english_str'.
      }
  }

% オプションを指定して jlreq を読み込む
\LoadClass
  [
    paper=a4,
    fontsize=12pt,
    jafontsize=11.1pt,
    \bool_if:NF \g_atk_nogutter_bool { gutter=3cm, }
    \bool_if:NF \g_atk_oneside_bool { twoside }
  ] { jlreq }

% 英語対応
\bool_if:NT \g_atk_english_caption_bool
  {
    \tl_set:Nn \contentsname { Table~ of~ Contents }
    \tl_set:Nn \refname { References }
    \tl_set:Nn \indexname { Index }
    \tl_set:Nn \listfigurename { List~ of~ Figures }
    \tl_set:Nn \figurename { Figure }
    \tl_set:Nn \listtablename { List~ of~ Tables }
    \tl_set:Nn \tablename { Table }
    \tl_set:cn { fnum@figure } { \figurename\nobreakspace\thefigure }
    \tl_set:cn { fnum@table } { \tablename\nobreakspace\thetable }
  }

%% ここからはレガシーな実装が多い
%% 主に表紙等の設定を行う

% キャプションの設定
\setlength{\belowcaptionskip}{.25\baselineskip}

% 日本語のとき和暦をデフォルトにする
\bool_if:NF \g_atk_english_titlepage_bool { \和暦 }

% 年度の計算
\newcommand{\@nendo}{
  \str_new:N \l_atk_nengo_str
  \int_new:N \l_atk_academic_year_int
  \str_set:Nn \l_atk_nengo_str {  }
  \int_set:Nn \l_atk_academic_year_int { \year }
  \if西暦\else
    \bool_if:NF \g_atk_english_titlepage_bool
      {
        \int_compare:nNnTF { \year } < { 2019 }
          {
            \str_set:Nn \l_atk_nengo_str { 平成 }
            \int_set:Nn \l_atk_academic_year_int { \year - 1989 + 1 }
          }
          {
            \str_set:Nn \l_atk_nengo_str { 令和 }
            \int_set:Nn \l_atk_academic_year_int { \year - 2019 + 1 }
          }
      }
  \fi
  \int_compare:nNnT { \month } < { 4 } { \int_gdecr:Nn \l_atk_academic_year_int }

  \l_atk_nengo_str
  \int_compare:nNnTF { \l_atk_academic_year_int } = { 1 }
    { 元 } { \int_to_arabic:n { \l_atk_academic_year_int } }
  \bool_if:NTF \g_atk_english_titlepage_bool { ~ academic~ year,~ } { 年度 }
}

% 年度の手動設定
\newcommand*{\nendo}[1]{
  \renewcommand{\@nendo}{#1}
}

% 各設定
\newcommand{\@thesis}{卒業研究論文}
\newcommand*{\thesis}[1]{
  \renewcommand{\@thesis}{#1}
}
\newcommand{\@institution}{長岡工業高等専門学校}
\newcommand*{\institution}[1]{
  \renewcommand{\@institution}{#1}
}
\newcommand{\@department}{電子制御工学科}
\newcommand*{\department}[1]{
  \renewcommand{\@department}{#1}
}
\newcommand{\@laboratory}{視覚情報処理研究室}
\newcommand*{\laboratory}[1]{
  \renewcommand{\@laboratory}{#1}
}
\newcommand{\@supervisor}{高橋\　章}
\newcommand*{\supervisor}[1]{
  \renewcommand{\@supervisor}{#1}
}

% 英語対応（英語に自信が無い）
\bool_if:NT \g_atk_english_titlepage_bool
  {
    \thesis{Graduation~ thesis}
    \institution{NIT,~ Nagaoka~ College}
    \department{Department~ of~ Electronic~ Control~ Engineering}
    \laboratory{Visual~ Information~ Processing~ Research~ Lab}
    \supervisor{Akira~ Takahashi}
    \date{%
      \ifcase\the\month \or January\or February\or March\or April\or May\or June\or
      July\or August\or September\or October\or November\or December\fi
      \space\the\day,~ \the\year}
  }

% 専攻科の設定
\bool_if:NT \g_atk_ac_bool
  {
    \bool_if:NTF \g_atk_english_titlepage_bool
      {
        \thesis{Advanced~ Course~ thesis}
        \department{Electrical~ \&~ Mechanical~ Systems~ Engineering~ Advanced~ Course}
      }
      {
        \thesis{特別研究論文}
        \department{電子機械システム工学専攻}
      }
  }

\newcommand{\clearsettings}{
  \global\let\@title\@empty
  \global\let\title\relax
  \global\let\@author\@empty
  \global\let\author\relax
  \global\let\@date\@empty
  \global\let\date\relax
  \global\let\@thanks\@empty
  \global\let\thanks\relax
  \global\let\and\relax
  \global\let\@nendo\relax
  \global\let\nendo\relax
  \global\let\@thesis\relax
  \global\let\thesis\relax
  \global\let\@institution\relax
  \global\let\institution\relax
  \global\let\@department\relax
  \global\let\department\relax
  \global\let\@laboratory\relax
  \global\let\laboratory\relax
  \global\let\@supervisor\relax
  \global\let\supervisor\relax
  \global\let\maketitle\relax
}

% \maketitleの設定（表紙と目次）
\renewcommand{\maketitle}{%
  \pagenumbering{alph}
  \begin{titlepage}%
    \let\footnotesize\small
    \let\footnoterule\relax
    \let\footnote\thanks
    \null\vfil
    \vskip 3\baselineskip%
    \centering%
    {\Large {\@nendo}\@thesis\par}%
    \vskip 3\baselineskip%
    {\LARGE\textbf{\@title}\par}%
    \vskip 3\baselineskip%
    {\large%
      \@institution\\
      \@department\\
      \@laboratory\\
      \bool_if:NTF \g_atk_english_titlepage_bool
        { (Supervisor\ \ \@supervisor) }
        { （指導教員\　\　\@supervisor） }
      \par%
    }%
    \vskip 3\baselineskip%
    {\Large \@author\par}%
    \vskip 3\baselineskip%
    {\large \@date \par}%
    \par%
    \@thanks
    \vfil\null
  \end{titlepage}%
  \cleardoublepage
  \pagenumbering{roman}
  \tableofcontents
  \cleardoublepage
  \pagenumbering{arabic}
  \setcounter{footnote}{0}%
  \clearsettings
}

% 参考文献（フォントサイズを small に変更）
\renewenvironment{thebibliography}[1]{%
  \jlreq@oldfontcommand@enable
  \section*{\refname}%
  \@mkboth{\refname}{\refname}%
  \small
  \list{\@biblabel{\@arabic\c@enumiv}}%
    {\settowidth\labelwidth{\@biblabel{#1}}%
    \labelsep=1\zw
    \leftmargin\labelwidth
    \advance\leftmargin\labelsep
    \itemindent=0pt
    \@openbib@code
    \usecounter{enumiv}%
    \let\p@enumiv\@empty
    \renewcommand\theenumiv{\@arabic\c@enumiv}}%
  \sloppy
  \clubpenalty4000
  \@clubpenalty\clubpenalty
  \widowpenalty4000%
  \sfcode`\.\@m
}{%
  \def\@noitemerr{\@latex@warning{Empty `thebibliography' environment}}%
  \endlist
  \jlreq@oldfontcommand@disable
}
