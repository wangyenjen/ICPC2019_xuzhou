#ifndef RANDDIST_H_
#define RANDDIST_H_

#include <cmath>
#include <limits>
#include <cstdint>
#include <algorithm>
#include <type_traits>

namespace CompLib {

template <class T> class Param2_ {
  T a_, b_;
 public:
  Param2_(T a, T b) : a_(a), b_(b) {}
  T a() const { return a_; }
  T b() const { return b_; }
  bool operator==(const Param2_& x) const { return a_ == x.a_ && b_ == x.b_; }
  bool operator!=(const Param2_& x) const { return !(*this == x); }
};

template <class T = int> class UniformIntDistribution {
 public:
  typedef T result_type;
  typedef Param2_<T> param_type;
 private:
  param_type param_;
 public:
  UniformIntDistribution(result_type a = 0, result_type b =
      std::numeric_limits<result_type>::max()) : param_(a, b) {}
  void reset() const {}
  param_type param() const { return param_; }
  void param(const param_type& par) { param_ = par; }
  result_type min() const { return param_.a(); }
  result_type max() const { return param_.b(); }
  result_type a() const { return param_.a(); }
  result_type b() const { return param_.b(); }
  bool operator==(const UniformIntDistribution& x) const {
    return param_ == x.param_;
  }
  bool operator!=(const UniformIntDistribution& x) const {
    return param_ != x.param_;
  }
  template <class Gen> result_type operator()(Gen& gen) const {
    return operator()(gen, param_);
  }
  template <class Gen> result_type operator()(Gen& gen,
      const param_type& param) const {
    typedef typename Gen::result_type GT_;
    typedef typename std::make_unsigned<T>::type UT_;
    typedef typename std::common_type<GT_, UT_>::type Type;
    const Type gmin = gen.min();
    const Type grange = gen.max() - gmin;
    const Type urange = Type(param.b()) - Type(param.a());
    Type ret;
    if (grange > urange) {
      const Type scale = grange / (urange + 1);
      const Type lim = (urange + 1) * scale;
      do {
        ret = Type(gen()) - gmin;
      } while (ret >= lim);
      ret /= scale;
    } else if (grange < urange) {
      Type tmp;
      do {
        const Type grange1 = grange + 1;
        tmp = (grange1) * operator()(gen, param_type(0, urange / grange1));
        ret = tmp + Type(gen()) - gmin;
      } while (ret > urange || ret < tmp);
    } else {
      ret = Type(gen()) - gmin;
    }
    return ret + param.a();
  }
};

template <class T, size_t bits, class Gen> T GenerateCanonical(Gen& gen) {
  static_assert(std::is_floating_point<T>::value,
      "template argument must be a floating point type");
  using Float = double;
  const size_t b = std::min(static_cast<size_t>(
      std::numeric_limits<T>::digits), bits);
  const double r = static_cast<Float>(gen.max()) -
      static_cast<Float>(gen.min()) + 1.0L;
  const size_t log2r = std::log2(r);
  const size_t m = std::max<size_t>(1UL, (b + log2r - 1UL) / log2r);
  T ret, sum = T(0), tmp = T(1);
  for (size_t k = m; k != 0; k--) {
    sum += T(gen() - gen.min()) * tmp;
    tmp *= r;
  }
  ret = sum / tmp;
  if (ret >= T(1)) ret = std::nextafter(T(1), T(0));
  return ret;
}
template <class T, class Gen> inline T GenerateCanonical(Gen& gen) {
  return GenerateCanonical<T, std::numeric_limits<T>::digits, Gen>(gen);
}

template <class T = double> class UniformRealDistribution {
 public:
  typedef T result_type;
  typedef Param2_<T> param_type;
 private:
  param_type param_;
 public:
  UniformRealDistribution(result_type a = 0., result_type b = 1.) :
      param_(a, b) {}
  void reset() const {}
  param_type param() const { return param_; }
  void param(const param_type& par) { param_ = par; }
  result_type min() const { return param_.a(); }
  result_type max() const { return param_.b(); }
  result_type a() const { return param_.a(); }
  result_type b() const { return param_.b(); }
  bool operator==(const UniformRealDistribution& x) const {
    return param_ == x.param_;
  }
  bool operator!=(const UniformRealDistribution& x) const {
    return param_ != x.param_;
  }
  template <class Gen> result_type operator()(Gen& gen) const {
    return operator()(gen, param_);
  }
  template <class Gen> result_type operator()(Gen& gen,
      const param_type& param) const {
    return GenerateCanonical<T, Gen>(gen) * (param.b() - param.a()) + param.a();
  }
};

template <class T, class Gen>
std::pair<T, T> GenTwoUniformInts_(T b0, T b1, Gen&& g) {
  T x = UniformIntDistribution<T>{0, (b0 * b1) - 1}(g);
  return std::make_pair(x / b1, x % b1);
}

template <class Iter, class Gen_> void Shuffle(Iter first, Iter last, Gen_&& g) {
  if (first == last) return;
  typedef typename std::iterator_traits<Iter>::difference_type Diff_;
  typedef typename std::make_unsigned<Diff_>::type UD_;
  typedef UniformIntDistribution<UD_> Distr_;
  typedef typename Distr_::param_type Param_;
  typedef typename std::remove_reference<Gen_>::type Gen;
  typedef typename std::common_type<typename Gen::result_type, UD_>::type UC_;

  const UC_ urngrange = g.max() - g.min();
  const UC_ urange = UC_(last - first);
  if (urngrange / urange >= urange) {
    Iter i = first + 1;
    if ((urange % 2) == 0) {
      Distr_ d{0, 1};
      std::iter_swap(i++, first + d(g));
    }
    while (i != last) {
      const UC_ swap_range = UC_(i - first) + 1;
      const std::pair<UC_, UC_> pospos =
          GenTwoUniformInts_(swap_range, swap_range + 1, g);
      std::iter_swap(i++, first + pospos.first);
      std::iter_swap(i++, first + pospos.second);
    }
    return;
  }
  Distr_ d;
  for (Iter i = first + 1; i != last; ++i) {
    std::iter_swap(i, first + d(g, Param_(0, i - first)));
  }
}

uint64_t HashTwo(uint64_t a, uint64_t b) {
  static const uint64_t table[3] = {0x9e3779b185ebca87, 0xc2b2ae3d27d4eb4f, 0x165667b19e3779f9};
  auto Mix = [](uint64_t a, uint64_t b) {
    a += b * table[1];
    a = (a << 31) | (a >> 33);
    return a * table[0];
  };
  uint64_t v1 = Mix(-table[0], a);
  uint64_t v2 = Mix(table[1], b);
  uint64_t ret = ((v1 << 18) | (v1 >> 46)) + ((v2 << 7) | (v2 >> 57));
  ret ^= ret >> 33;
  ret *= table[1];
  ret ^= ret >> 29;
  ret *= table[2];
  ret ^= ret >> 32;
  return ret;
}

uint64_t HashArgs(int argc, char** argv) {
  uint64_t x = 0;
  for (int i = 1; i < argc; i++) {
    for (int j = 0; argv[i][j]; j++) x = HashTwo(x, argv[i][j]);
  }
  return x;
}

} // namespace CompLib

#endif
