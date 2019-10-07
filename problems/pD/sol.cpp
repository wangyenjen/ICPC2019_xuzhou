#include <cmath>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <unordered_map>

template <class T> struct Point {
  T x, y, z;
  bool operator==(const Point& a) const {
    return x == a.x && y == a.y && z == a.z;
  }
  bool operator!=(const Point& a) const {
    return !(*this == a);
  }
  Point<T>& operator+=(const Point& a) {
    x += a.x; y += a.y; z += a.z; return *this;
  }
  Point<T>& operator-=(const Point& a) {
    x -= a.x; y -= a.y; z -= a.z; return *this;
  }
  Point<T>& operator*=(const T& a) {
    x *= a; y *= a; z *= a; return *this;
  }
  Point<T>& operator/=(const T& a) {
    static_assert(std::is_floating_point<T>::value, "T must be a floating point type");
    x /= a; y /= a; z /= a; return *this;
  }
};

template <class T> Point<T> operator+(const Point<T>& a, const Point<T>& b) {
  Point<T> ret(a); ret += b; return ret;
}
template <class T> Point<T> operator-(const Point<T>& a, const Point<T>& b) {
  Point<T> ret(a); ret -= b; return ret;
}
template <class T> Point<T> operator*(const Point<T>& a, const T& b) {
  Point<T> ret(a); ret *= b; return ret;
}
template <class T> Point<T> operator*(const T& b, const Point<T>& a) {
  Point<T> ret(a); ret *= b; return ret;
}
template <class T> Point<T> operator/(const Point<T>& a, const T& b) {
  Point<T> ret(a); ret /= b; return ret;
}

template <class T> struct Edge {
  Point<T> start;
  Edge<T>* next;
  Edge<T>* dual;
};
template <class T> using Polyhedron = std::vector<Edge<T>*>;
template <class T> struct Plane {
  Point<T> point, normal;
};

template <class T> T Dot(const Point<T>& a, const Point<T>& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}
template <class T> Point<T> Cross(const Point<T>& a, const Point<T>& b) {
  return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}
template <class T> Point<T> Normal(const Point<T>& a) {
  static_assert(std::is_floating_point<T>::value, "T must be a floating point type");
  return a / std::sqrt(Dot(a, a));
}
template <class T> Point<T> Projection(const Point<T>& a, const Point<T>& b) {
  static_assert(std::is_floating_point<T>::value, "T must be a floating point type");
  return b * (Dot(a, b) / Dot(b, b));
}

template <class T> Point<T> IntersectPoint(
    const Plane<T>& pl, const Edge<T>& ed) {
  static_assert(std::is_floating_point<T>::value, "T must be a floating point type");
  Point<T> dir = ed.next->start - ed.start;
  T t = Dot(pl.normal, pl.point - ed.start) / Dot(pl.normal, dir);
  return ed.start + dir * t;
}

template <class T> T PlanePoint(const Plane<T>& pl, const Point<T>& pt) {
  return Dot(pl.normal, pt - pl.point);
}

// poly reserves +normal poly; return -normal poly
// poly is a triangulated polyhedron
template <class T> Polyhedron<T> Slice(
    Polyhedron<T>& poly, const Plane<T>& pl, T eps = 1e-6) {
  static_assert(std::is_floating_point<T>::value, "T must be a floating point type");
  auto CutEdge = [&](Edge<T>* now, const Point<T>& pt) {
    Edge<T> *n2 = now->next, *n3 = n2->next;
    Edge<T> *a1 = new Edge<T>, *a2 = new Edge<T>, *a3 = new Edge<T>;
    *a1 = {now->start, a2, nullptr}; // start, next, dual
    *a2 = {pt, n3, a3};
    *a3 = {n3->start, now, a2};
    now->start = pt;
    n2->next = a3;
    n3->next = a1;
    poly.push_back(a1);
    poly.push_back(a2);
    poly.push_back(a3);
    return a1;
  };
  Edge<T>* start = nullptr;
  { // cut all faces by the plane
    bool pos = false, neg = false;
    for (size_t i = 0; i < poly.size(); i++) {
      // note that poly will be appended, so poly.size() will change!
      T val1 = PlanePoint(pl, poly[i]->start);
      T val2 = PlanePoint(pl, poly[i]->next->start);
      if (val1 > eps) pos = true;
      if (val1 < -eps) neg = true;
      if (val1 > eps && val2 < -eps) {
        Edge<T> *now = poly[i], *dual = now->dual;
        Point<T> inter = IntersectPoint(pl, *poly[i]);
        Edge<T> *a1 = CutEdge(now, inter), *a2 = CutEdge(dual, inter);
        now->dual = a2; a2->dual = now;
        dual->dual = a1; a1->dual = dual;
      } else if (!start && std::abs(val1) <= eps && std::abs(val2) <= eps) {
        start = poly[i];
      }
    }
    if (!neg) return Polyhedron<T>();
    if (!pos) {
      Polyhedron<T> ret;
      ret.swap(poly);
      return ret;
    }
  }
  if (!start) throw;
  Polyhedron<T> ret;
  { // move edges on the negative side
    // note that any cut edge and its dual will be on different side
    size_t N = std::partition(poly.begin(), poly.end(), [&](const Edge<T>* a){
      const Edge<T> *b = a->next, *c = b->next;
      return PlanePoint(pl, a->start) >= -eps &&
            PlanePoint(pl, b->start) >= -eps &&
            PlanePoint(pl, c->start) >= -eps;
    }) - poly.begin();
    for (; poly.size() > N; poly.pop_back()) ret.push_back(poly.back());
  }
  if (PlanePoint(pl, start->next->next->start) < -eps) start = start->dual;
  auto FindNext = [&](Edge<T>* now) {
    for (now = now->next;; now = now->dual->next) {
      if (std::abs(PlanePoint(pl, now->next->start)) <= eps) break;
    }
    return now;
  };
  Edge<T> *prv_a3 = start, *prv_b3 = start->dual;
  for (Edge<T>* now = FindNext(start);;) {
    if (now->next->start == start->start) { // finalize
      Edge<T> *dual = now->dual;
      now->dual = prv_a3;
      prv_a3->dual = now;
      dual->dual = prv_b3;
      prv_b3->dual = dual;
      break;
    }
    Edge<T> *nxt = FindNext(now);
    Edge<T> *a1 = new Edge<T>, *a2 = new Edge<T>, *a3 = new Edge<T>;
    Edge<T> *b1 = new Edge<T>, *b2 = new Edge<T>, *b3 = new Edge<T>;
    Edge<T> *dual = now->dual;
    *a1 = {now->next->start, a2, now};
    *a2 = {now->start, a3, prv_a3};
    *a3 = {start->start, a1, nullptr};
    now->dual = a1;
    prv_a3->dual = a2;
    *b1 = {a2->start, b3, dual};
    *b2 = {a3->start, b1, prv_b3};
    *b3 = {a1->start, b2, nullptr};
    dual->dual = b1;
    prv_b3->dual = b2;
    poly.push_back(a1); poly.push_back(a2); poly.push_back(a3);
    ret.push_back(b1); ret.push_back(b2); ret.push_back(b3);
    prv_a3 = a3, prv_b3 = b3;
    now = nxt;
  }
  return ret;
}

// poly is a triangulated polyhedron
template <class T> T Volume(const Polyhedron<T>& poly) {
  T ans = 0;
  for (auto& p1 : poly) {
    Edge<T> *p2 = p1->next, *p3 = p2->next;
    ans += Dot(p1->start, Cross(p2->start, p3->start));
  }
  return std::abs(ans) / 18; // each face will be calculated 3 times
}

template <class T> void Triangulate(Polyhedron<T>& poly) {
  // poly.size() will change!
  size_t N = poly.size();
  for (size_t i = 0; i < N; i++) {
    Edge<T>* now = poly[i];
    if (now->next->next->next == now) continue;
    for (Edge<T> *prv = now, *i = now->next;;) {
      if (i->next->next == now) {
        i->next->next = prv;
        break;
      }
      Edge<T> *nxt = i->next;
      Edge<T> *a = new Edge<T>, *b = new Edge<T>;
      *a = {i->next->start, prv, b};
      *b = {now->start, i->next, a};
      poly.push_back(a);
      poly.push_back(b);
      i->next = a;
      prv = b;
      i = nxt;
    }
  }
}

template <class T> Polyhedron<T> GenPolyhedron(
    const std::vector<Point<T>>& pt, const std::vector<std::vector<int>>& ed) {
  static_assert(std::is_floating_point<T>::value, "T must be a floating point type");
  struct Node {
    int p;
    T val;
    bool neg;
    bool operator<(const Node& x) const {
      if (neg != x.neg) return neg; // clockwise from outside
      return neg ? val > x.val : val < x.val;
    }
  };
  Polyhedron<T> ret;
  std::vector<std::unordered_map<int, Edge<T>*>> mp(pt.size());
  for (int i = 0; i < (int)pt.size(); i++) {
    Point<T> o = pt[i];
    Point<T> b = ((pt[ed[i][0]] - o) + (pt[ed[i][1]] - o)) * (T)0.5;
    Point<T> c = (pt[ed[i][0]] - o) - Projection(pt[ed[i][0]] - o, b);
    std::vector<Node> nd;
    for (int j : ed[i]) {
      Point<T> q = Normal((pt[j] - o) - Projection(pt[j] - o, b));
      nd.push_back({j, Dot(q, c), Dot(b, Cross(q, c)) >= 0});
    }
    std::sort(nd.begin(), nd.end());
    Edge<T> *first = nullptr, *prev = nullptr;
    for (auto& j : nd) {
      Edge<T> *a1, *a2;
      auto it = mp[i].find(j.p);
      if (it == mp[i].end()) {
        a1 = new Edge<T>;
        a2 = new Edge<T>;
        *a1 = {pt[i], nullptr, a2};
        *a2 = {pt[j.p], nullptr, a1};
        ret.push_back(a1);
        ret.push_back(a2);
        mp[j.p].insert({i, a2});
      } else {
        a1 = it->second;
        a2 = a1->dual;
        mp[i].erase(it);
      }
      if (!first) first = a1;
      if (prev) prev->next = a1;
      prev = a2;
    }
    prev->next = first;
  }
  return ret;
}

#include <cstdio>

using Data = long double;

int main() {
  int N, M, K;
  scanf("%d%d%d", &N, &M, &K);
  std::vector<Point<Data>> pts(N);
  std::vector<std::vector<int>> ed(N);
  for (int i = 0; i < N; i++) {
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    pts[i] = {(Data)x, (Data)y, (Data)z};
  }
  for (int i = 0; i < M; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    ed[a].push_back(b);
    ed[b].push_back(a);
  }
  std::vector<Polyhedron<Data>> poly;
  poly.emplace_back(GenPolyhedron(pts, ed));
  Triangulate(poly[0]);
  for (int i = 0; i < K; i++) {
    Plane<Data> pl;
    int a, b, c, d; // ax + by + cz = d
    scanf("%d%d%d%d", &a, &b, &c, &d);
    pl.normal = {(Data)a, (Data)b, (Data)c};
    if (a >= b && a >= c) {
      pl.point = {(Data)d / a, 0, 0};
    } else if (b >= a && b >= c) {
      pl.point = {0, (Data)d / b, 0};
    } else {
      pl.point = {0, 0, (Data)d / c};
    }
    for (int j = 0; j < (1 << i); j++) poly.emplace_back(Slice(poly[j], pl));
  }
  std::vector<Data> ans;
  for (auto& i : poly) ans.push_back(Volume(i));
  std::sort(ans.begin(), ans.end());
  for (Data i : ans) printf("%.9Lf\n", i);
}
