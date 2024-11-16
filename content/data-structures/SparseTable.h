/**
 * Author: tourist
 * Description: Zero-indexed, pass in vector 
 * Usage:  
 *  SparseTable<int> st(a, [\&](int i, int j) { return min(i, j); });
 */
template <typename T, class F = function<T(const T&, const T&)>>
class SparseTable {
 public:
  int _n;
  vector<vector<T>> mat;
  F func;

  SparseTable(const vector<T>& a, const F& f) : func(f) {
    _n = static_cast<int>(a.size());
    int max_log = 32 - __builtin_clz(_n);
    mat.resize(max_log);
    mat[0] = a;
    for (int j = 1; j < max_log; j++) {
      mat[j].resize(_n - (1 << j) + 1);
      for (int i = 0; i <= _n - (1 << j); i++) {
        mat[j][i] = func(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  T get(int from, int to) const {
    /*assert(0 <= from && from <= to && to <= _n - 1);*/
    int lg = 32 - __builtin_clz(to - from + 1) - 1;
    return func(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
  }
};
