#ifndef PHYSUTILS_VECTOR_HELPER_H
#define PHYSUTILS_VECTOR_HELPER_H

#include <vector>
#include <algorithm>
#include <ostream>
#include <numeric>

/** stream operator for stl containers. */
template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& c)
{
  if (c.empty()) {
    os << "-empty-";
    return os;
  }

  os << "[";
  auto it = c.cbegin();
  for(; it != c.cend() - 1; ++it) { os << *it << ", " ;}
  os << c.back() << "]";

  return os;
}

/** calculate the average value of all values in the passed containenr. */
template<class C>
inline double mean(const C& v)
{
  size_t nEntries = v.size();
  return std::accumulate(v.cbegin(), v.cend(), 0.0) / (double) nEntries;
}

/** calculate the (sample) standard deviation of all values in the container given the mean of the values. */
template<class C>
inline double stddev(const C& v, const double mean)
{
  double sum2dev = 0;
  for (const auto& val : v) sum2dev += (val - mean) * (val - mean);

  return std::sqrt(sum2dev / (v.size() - 1));
}

/** calculate the (sample) standard deviation of all values in the container. */
template<class C>
inline double stddev(const C& v)
{
  return stddev(v, mean(v));
}

/** check if any element of the container fulfills the predicate. */
template<class C, class P>
inline bool any(const C& v, P pred)
{
  for (const auto& e : v) {
    if (pred(e)) return true;
  }
  return false;
}

/** create a vector with evenly spaced values between min and max (see MATLABs linspace). */
template<typename T>
std::vector<T> linspace(const T min, const T max, const size_t steps)
{
  std::vector<T> vals;
  const T step = (max - min) / (steps - 1);
  for (size_t i = 0; i < steps; ++i) {
    vals.push_back(min + i * step);
  }
  return vals;
}

#endif
