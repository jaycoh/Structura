#ifndef OCTREE_H
#define OCTREE_H

#include <memory>
#include <stdexcept>

class Point3 {
public:
    Point3(int x, int y, int z) : x(x), y(y), z(z) {}
    int getX() const { return x; }
    int getY() const { return y; }
    int getZ() const { return z; }

private:
    int x;
    int y;
    int z;
};

template <typename T>
class Octree {
public:
    Octree(Point3 minCorner, Point3 maxCorner)
        : minCorner_(minCorner), maxCorner_(maxCorner) {
        if (minCorner_.getX() >= maxCorner_.getX() ||
            minCorner_.getY() >= maxCorner_.getY() ||
            minCorner_.getZ() >= maxCorner_.getZ()) {
            throw std::invalid_argument("Invalid bounds");
        }
    }

    void insert(const Point3& point, const T& data) {
        if (!isInBoundary(point)) {
            throw std::runtime_error("Point out of boundary");
        }
        insertImpl(point, data);
    }

    const T* search(const Point3& point) const {
        if (!isInBoundary(point)) {
            return nullptr;
        }
        return searchImpl(point);
    }

private:
    Point3 minCorner_;
    Point3 maxCorner_;
    std::unique_ptr<T> data_;
    Point3 point_{0, 0, 0};
    bool hasPoint_ = false;
    std::unique_ptr<Octree> children_[8];

    bool isInBoundary(const Point3& p) const {
        return p.getX() >= minCorner_.getX() && p.getX() <= maxCorner_.getX() &&
               p.getY() >= minCorner_.getY() && p.getY() <= maxCorner_.getY() &&
               p.getZ() >= minCorner_.getZ() && p.getZ() <= maxCorner_.getZ();
    }

    void insertImpl(const Point3& point, const T& data) {
        if (hasPoint_ && !children_[0]) {
            Point3 existingPoint = point_;
            T existingData = std::move(*data_);
            data_.reset();
            hasPoint_ = false;
            splitAndInsert(existingPoint, existingData);
        }

        if (!children_[0]) {
            point_ = point;
            data_ = std::make_unique<T>(data);
            hasPoint_ = true;
            return;
        }

        int midX = (minCorner_.getX() + maxCorner_.getX()) / 2;
        int midY = (minCorner_.getY() + maxCorner_.getY()) / 2;
        int midZ = (minCorner_.getZ() + maxCorner_.getZ()) / 2;

        int octant = 0;
        // Determine octant based on > mid comparisons
        if (point.getX() > midX) octant |= 1; // x high
        if (point.getY() > midY) octant |= 2; // y high
        if (point.getZ() > midZ) octant |= 4; // z high

        if (!children_[octant]) {
            // compute bounds for child
            int minX = (octant & 1) ? midX : minCorner_.getX();
            int maxX = (octant & 1) ? maxCorner_.getX() : midX;
            int minY = (octant & 2) ? midY : minCorner_.getY();
            int maxY = (octant & 2) ? maxCorner_.getY() : midY;
            int minZ = (octant & 4) ? midZ : minCorner_.getZ();
            int maxZ = (octant & 4) ? maxCorner_.getZ() : midZ;
            children_[octant] = std::make_unique<Octree>(Point3(minX, minY, minZ), Point3(maxX, maxY, maxZ));
        }
        children_[octant]->insertImpl(point, data);
    }

    void splitAndInsert(const Point3& existingPoint, const T& existingData) {
        int midX = (minCorner_.getX() + maxCorner_.getX()) / 2;
        int midY = (minCorner_.getY() + maxCorner_.getY()) / 2;
        int midZ = (minCorner_.getZ() + maxCorner_.getZ()) / 2;

        // create 8 children
        for (int ox = 0; ox <= 1; ++ox) {
            for (int oy = 0; oy <= 1; ++oy) {
                for (int oz = 0; oz <= 1; ++oz) {
                    int idx = (ox) | (oy << 1) | (oz << 2);
                    int cminX = ox ? midX : minCorner_.getX();
                    int cmaxX = ox ? maxCorner_.getX() : midX;
                    int cminY = oy ? midY : minCorner_.getY();
                    int cmaxY = oy ? maxCorner_.getY() : midY;
                    int cminZ = oz ? midZ : minCorner_.getZ();
                    int cmaxZ = oz ? maxCorner_.getZ() : midZ;
                    children_[idx] = std::make_unique<Octree>(Point3(cminX, cminY, cminZ), Point3(cmaxX, cmaxY, cmaxZ));
                }
            }
        }

        insertImpl(existingPoint, existingData);
    }

    const T* searchImpl(const Point3& point) const {
        if (!children_[0] && hasPoint_ && point_.getX() == point.getX() && point_.getY() == point.getY() && point_.getZ() == point.getZ()) {
            return data_.get();
        }

        if (!children_[0]) return nullptr;

        int midX = (minCorner_.getX() + maxCorner_.getX()) / 2;
        int midY = (minCorner_.getY() + maxCorner_.getY()) / 2;
        int midZ = (minCorner_.getZ() + maxCorner_.getZ()) / 2;

        int octant = 0;
        if (point.getX() > midX) octant |= 1;
        if (point.getY() > midY) octant |= 2;
        if (point.getZ() > midZ) octant |= 4;

        return children_[octant] ? children_[octant]->searchImpl(point) : nullptr;
    }
};

#endif // OCTREE_H
