// Author: Bjorn Wehlin

#pragma once

#include <ostream>
#include <fstream>
#include <vector>
#include <memory>

namespace sf
{
  /*
    Helper class for writing Matplotlib plotting scripts for Python

    The user's PointT class must have .x and .y as public member variables,
    and PointTs should be both default-constructible as well as constructible
    with (x, y) as arguments.

    The user's RectangleT class must have .bottomLeft and .topRight as public
    member variables (of type PointT).

    Usage:

    Assuming Point and Rectangle are the user's types.

    MplWriter<Point, Rectangle> writer("plot.py");

    for each rectangle 'rect':
    writer << rect;

    for each point vector 'points':
    writer << points;

    As an optional argument, the user may select the marker size to be used.
    The appropriate marker size will depend on the input data.

  */

  template <typename PointT, typename RectangleT>
  class MplWriter
  {
  public:
    MplWriter(std::ostream& os, double markerSize = 0.5)
      : m_os(os)
    {
      writePreamble(markerSize);
    }

    MplWriter(const std::string& filename, double markerSize = 0.5)
      : m_ofs(std::make_unique<std::ofstream>(filename))
      , m_os(*m_ofs)
    {
      writePreamble(markerSize);
    }

    ~MplWriter()
    {
      m_os << "ax.axis('equal')\n";
      m_os << "plt.show()\n";
    }

    MplWriter(const MplWriter&) = delete;
    MplWriter& operator=(const MplWriter&) = delete;

    MplWriter& operator<<(const std::vector<PointT>& points)
    {
      if (points.empty())
      {
        return *this;
      }

      m_os << "scatter(ax, [";
      for (auto const& pt : points)
      {
        m_os << pt.x << ", ";
      }
      m_os << "], [";
      for (auto const& pt : points)
      {
        m_os << pt.y << ", ";
      }

      m_os << "])\n";

      return *this;
    }

    MplWriter& operator<<(const RectangleT& rect)
    {
      m_os << "r = plt.Rectangle([" << rect.bottomLeft.x << ", " << rect.bottomLeft.y << "], "
        << (rect.topRight.x - rect.bottomLeft.x) << ", " << (rect.topRight.y - rect.bottomLeft.y)
        << ", fill=False)\n";
      m_os << "ax.add_patch(r)\n";

      return *this;
    }

  private:
    void writePreamble(double markerSize)
    {
      m_os << "import matplotlib.pyplot as plt\n";
      m_os << "def scatter(ax, x, y):\n";
      m_os << "  ax.scatter(x, y, s=" << markerSize << ")\n";

      m_os << "fig, ax = plt.subplots(1,1, constrained_layout=True)\n";
    }

    std::unique_ptr<std::ofstream> m_ofs;
    std::ostream& m_os;

  };
}