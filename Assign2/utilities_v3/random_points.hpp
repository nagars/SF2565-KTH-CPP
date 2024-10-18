// Author: Bjorn Wehlin

#pragma once

#include <random>
#include <vector>

namespace sf
{
  /*
  
    Helper class for generating random points.

    The user's PointT class must have .x and .y as public member variables,
    and PointTs should be both default-constructible as well as constructible
    with (x, y) as arguments.

    Usage: (assuming PointT = Point)

    sf::RandomPointGenerator<Point> generator; // Use default seed (not reproducible)
    sf::RandomPointGenerator<Point> generator{ 2565 }; // Use 2565 as the seed (reproducible)

    generator.addNormalPoints(1000);                      // Adds 1000 standard normal random points
    generator.addNormalPoints(1000, PointT{2.0, 3.0});    // Adds 1000 normal random points with mean (2.0, 3.0) and unit variance
    generator.addUniformPoints(1000, PointT{ 4.0, 0.0 }); // Adds 1000 uniformly distributed points in the square 3 < x < 5, -1 < y < 1
  
    auto points = generator.takePoints(); // Gets the randomly generated points and resets the generator's points.
                                          // auto type is std::vector<PointT>

  */

  template <class PointT>
  class RandomPointGenerator
  {
  public:
    RandomPointGenerator()
      : m_rndGen(std::random_device{}())
    { }

    RandomPointGenerator(size_t seed)
      : m_rndGen({ seed })
    { }

    const std::vector<PointT>& points() const { return m_points; }

    std::vector<PointT> takePoints()
    {
      std::vector<PointT> ret;
      m_points.swap(ret);
      return ret;
    }

    void addNormalPoints(size_t n, const PointT& mean = PointT{ 0., 0. })
    {
      addRandomPoints(n,
        std::normal_distribution<>(mean.x, 1.0),
        std::normal_distribution<>(mean.y, 1.0));
    }

    void addUniformPoints(size_t n, const PointT& mean = PointT{ 0., 0. })
    {
      addRandomPoints(n,
        std::uniform_real_distribution<>(mean.x - 1.0, mean.x + 1.0),
        std::uniform_real_distribution<>(mean.y - 1.0, mean.y + 1.0));
    }

    template <typename DistributionX, typename DistributionY>
    void addRandomPoints(size_t n, DistributionX distX, DistributionY distY)
    {
      size_t i = m_points.size();
      m_points.resize(m_points.size() + n);

      for (; i < m_points.size(); ++i)
      {
        m_points[i] = PointT{ distX(m_rndGen), distY(m_rndGen) };
      }
    }

  private:
    std::mt19937_64 m_rndGen; // Mersenne twister random engine
    std::vector<PointT> m_points;
  };

}