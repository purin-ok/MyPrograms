// import java.io.*;

class M3_1 {
  public static void main(String args[]) {
    int n, i, num_max, tmp;
    n = args.length;
    num_max = Integer.parseInt(args[0]);
    for (i = 1; i < n; i++) {
      tmp = Integer.parseInt(args[i]);
      if (num_max < tmp) {
        num_max = tmp;
      }
    }
    System.out.println("入力された値の最大値は" + num_max + "です．");
  }
}

class M3_2 {
  public static void main(String args[]) {
    int year = 0;
    switch (args[0]) {
      case "s":
      case "S":
        System.out.print("昭和");
        year = 1926 + Integer.parseInt(args[1]);
        break;

      case "h":
      case "H":
        System.out.print("平成");
        year = 1989 + Integer.parseInt(args[1]);
        break;

      case "r":
      case "R":
        System.out.print("令和");
        year = 2019 + Integer.parseInt(args[1]);
        break;

      default:
        break;
    }
    System.out.println(args[1] + "年は，西暦" + year + "年です．");
  }
}
