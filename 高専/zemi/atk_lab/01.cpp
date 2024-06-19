#include "./header/01.hpp"

#include "./header/IPbasic.hpp"

int main(int argc, char** argv) {
  // 引数処理
  if (argc != 2) {
    cerr << "usage:" << argv[0] << " file_val\n";
    return EXIT_FAILURE;
  }

  // ファイル読み込み
  ifstream input_file(argv[1]);
  if (input_file.fail()) {
    cout << "なにかがおかしい！" << endl;
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
        cout << "終わっとる" << endl;
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

  // 白黒反転処理
  for (j = 0; j < ymax; j++) {
    for (i = 0; i < xmax; i++) {
      matrix[j][i] = 1 - matrix[j][i];  // これで1は0に，0は1になる．
    }
  }

  output(matrix, xmax, ymax);

  // 左右反転処理
  flip_horizontal(matrix, xmax, ymax);
  output(matrix, xmax, ymax);

  // 上下反転処理
  flip_vertical(matrix, xmax, ymax);
  output(matrix, xmax, ymax);

  // 反時計回りに90度回転処理
  flip_horizontal(matrix, xmax, ymax);
  invert(matrix, xmax, ymax);
  output(matrix, xmax, ymax);

  // 時計回りに90度回転処理
  flip_vertical(matrix, xmax, ymax);
  invert(matrix, xmax, ymax);
  output(matrix, xmax, ymax);

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

void flip_horizontal(int** matrix, int x, int y) {
  int i, j;
  for (j = 0; j < y; j++) {
    for (i = 0; i < x / 2; i++) {
      int tmp = matrix[j][i];
      matrix[j][i] = matrix[j][x - i - 1];
      matrix[j][x - i - 1] = tmp;
    }
  }
  return;
}

void flip_vertical(int** matrix, int x, int y) {
  int i, j;
  for (j = 0; j < y / 2; j++) {
    for (i = 0; i < x; i++) {
      int tmp = matrix[j][i];
      matrix[j][i] = matrix[y - j - 1][i];
      matrix[y - j - 1][i] = tmp;
    }
  }
}

void invert(int** matrix, int x, int y) {
  int i, j;
  for (j = 0; j < y; j++) {
    for (i = j; i < x; i++) {
      int tmp = matrix[j][i];
      matrix[j][i] = matrix[i][j];
      matrix[i][j] = tmp;
    }
  }
  return;
}