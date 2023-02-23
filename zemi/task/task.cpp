#include "./header/task.hpp"

#include "../atk_lab/header/01.hpp"
#include "../atk_lab/header/IPbasic.hpp"

#define SITA 180
int main(int argc, char** argv) {
  // 引数処理
  if (argc != 2) {
    cerr << "usage:" << argv[0] << " file_val\n";
    return EXIT_FAILURE;
  }

  // ファイル読み込み
  ifstream input_file(argv[1]);
  if (input_file.fail()) {
    cout << "file is not looking" << endl;
    return EXIT_FAILURE;
  }

  // 画像処理
  string buf;
  string line;
  int i = 0, j = 0;
  int xmax, ymax;
  int** matrix;
  while (i < 2 && getline(input_file, line)) {  // 先頭二行の処理
    if (line[0] == '#') continue;
    if (!i) {  // i = 0
      string P = line;
      if (P != "P1") {
        cout << "this file is not P1." << endl;
        return 0;
      }
    }
    if (i) {  // i = 1
      istringstream iss(line);
      // 一行目切り貼りする
      getline(iss, buf, '\0');
      xmax = stoi(buf);
      getline(iss, buf, '\0');
      ymax = stoi(buf);
    }
    i++;
  }
  matrix = new int*[ymax];  // int*型をymax個生やす
  for (i = 0; i < ymax; i++) {
    matrix[i] = new int[xmax];  // int型をxmax子生やす
    // cout << i << endl;
  }

  for (j = 0; (j < ymax && getline(input_file, line)); j++) {
    std::istringstream iss(line);
    for (i = 0; (i < xmax && getline(iss, buf, ' ')); i++) {
      matrix[j][i] = stoi(buf);
    }
  }
  output(matrix, xmax, ymax);
  // これでmatrix内にデータの読み込みができた．
  // だからファイルを閉じる
  input_file.close();

  // ここから直線検出
  // 初期化
  int row = sqrt(xmax * xmax + ymax * ymax);
  int k = 0, distance = 0, rmax, sitamax;
  int** rsita;

  rsita = new int*[row];  // int*型をrow個生やす
  for (i = 0; i < row; i++) {
    rsita[i] = new int[SITA];  // int型をSITA子生やす
    // cout << i << endl;
  }

  for (j = 0; j < row; j++) {
    for (i = 0; i < SITA; i++) {
      rsita[j][i] = 0;
    }
  }

  for (j = 0; j < ymax; j++) {
    for (i = 0; i < xmax; i++) {  // すべての座標に対して
      if (matrix[j][i] == 1) {    // 点があるなら
        for (k = 0; k < SITA; k++) {
          distance = round((xmax / 2 - i) * cos(k * M_PI / 180) +
                           (ymax / 2 - j) * sin(k * M_PI / 180));
          rsita[distance + row / 2][k] += 1;
        }
      }
    }
  }

  cout << distance + row / 2 << endl;
  int max_rsita = 0;

  for (j = 0; j < row; j++) {
    for (i = 0; i < SITA; i++) {
      cout << rsita[j][i] << " ";
      if (max_rsita < rsita[j][i]) {
        max_rsita = rsita[j][i];
      }
    }
    cout << endl;
  }

  cout << max_rsita << endl;

  for (j = 0; j < row; j++) {
    for (i = 0; i < SITA; i++) {
      if (max_rsita == rsita[j][i]) {
        cout << "r = " << j - row / 2 << ", θ = " << i << "°" << endl;
      }
    }
  }

  // メモリ海王
  for (i = 0; i < ymax; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
  return EXIT_SUCCESS;
}

void output(int** matrix, int x, int y) {
  int i, j;
  cout << "表示開始" << endl;
  for (j = 0; j < y; j++) {
    for (i = 0; i < x; i++) {
      cout << matrix[j][i] << ' ';
    }
    cout << endl;
  }
  cout << "表示完了" << endl;
  return;
}
