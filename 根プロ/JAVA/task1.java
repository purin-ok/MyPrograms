// import java.io.*;

class M3_1 {
  public static void main(String args[]) {
    int n, i, num_max, tmp;
    // コマンドライン引数の配列の長さをnに入れる．
    n = args.length;
    // 初期設定をするためにコマンドライン引数の1つ目の引数を最大値変数の初期値とする．0や-3とかのマジックナンバーで初期化するのはマズい．
    num_max = Integer.parseInt(args[0]);
    for (i = 1; i < n; i++) {
      // i個目の引数と最大値変数を比べ，i個目の引数が大きければ上書き
      tmp = Integer.parseInt(args[i]);
      if (num_max < tmp) {
        num_max = tmp;
      }
    }
    // 出力
    System.out.println("入力された値の最大値は" + num_max + "です．");
  }
}

class M3_2 {
  public static void main(String args[]) {
    int year = 0;
    // switch(data){case c: ..... } のとき，data==cであれば，case c:より後の処理を行う．
    switch (args[0]) {
      // 昭和であれば表示
      case "s":
      case "S":
        System.out.print("昭和");
        year = 1926 + Integer.parseInt(args[1]);
        break;

      // 平成であれば行う
      case "h":
      case "H":
        System.out.print("平成");
        year = 1989 + Integer.parseInt(args[1]);
        break;

      // 令和であれば行う
      case "r":
      case "R":
        System.out.print("令和");
        year = 2019 + Integer.parseInt(args[1]);
        break;

      // 上のどれでもなければ行う
      default:
        break;
    }
    System.out.println(args[1] + "年は，西暦" + year + "年です．");
  }
}
