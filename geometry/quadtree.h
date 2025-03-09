#ifndef QUADTREE_H
#define QUADTREE_H

class Point {
public:
    Point(int x, int y) : x(x), y(y) {}
    int getX() const { return x; }
    int getY() const { return y; }

private:
    int x;
    int y;
};

template <typename T>
class Quadtree {
public:
    Quadtree(Point topLeft, Point bottomRight)
        : topLeft_(topLeft), bottomRight_(bottomRight) {
        if (topLeft_.getX() >= bottomRight_.getX() || topLeft_.getY() >= bottomRight_.getY()) {
            throw std::invalid_argument("Invalid bounds");
        }
    }

    void insert(const Point& point, const T& data) {
        if (!isInBoundary(point)) {
            throw std::runtime_error("Point out of boundary");
        }
        insertImpl(point, data);
    }

    const T* search(const Point& point) const {
        if (!isInBoundary(point)) {
            return nullptr;
        }
        return searchImpl(point);
    }

private:
    Point topLeft_;
    Point bottomRight_;
    std::unique_ptr<T> data_;
    Point point_{0, 0};
    bool hasPoint_ = false;
    std::unique_ptr<Quadtree> topLeftTree_;
    std::unique_ptr<Quadtree> topRightTree_;
    std::unique_ptr<Quadtree> bottomLeftTree_;
    std::unique_ptr<Quadtree> bottomRightTree_;

    bool isInBoundary(const Point& point) const {
        return point.getX() >= topLeft_.getX() && point.getX() <= bottomRight_.getX() &&
               point.getY() >= topLeft_.getY() && point.getY() <= bottomRight_.getY();
    }

    void insertImpl(const Point& point, const T& data) {
        if (hasPoint_ && !topLeftTree_) {
            Point existingPoint = point_;
            T existingData = std::move(*data_);
            data_.reset();
            hasPoint_ = false;
            splitAndInsert(existingPoint, existingData);
        }
        if (!topLeftTree_) {
            point_ = point;
            data_ = std::make_unique<T>(data);
            hasPoint_ = true;
            return;
        }

        int midX = (topLeft_.getX() + bottomRight_.getX()) / 2;
        int midY = (topLeft_.getY() + bottomRight_.getY()) / 2;

        if (point.getX() <= midX) {
            if (point.getY() <= midY) {
                if (!topLeftTree_) {
                    topLeftTree_ = std::make_unique<Quadtree>(topLeft_, Point(midX, midY));
                }
                topLeftTree_->insertImpl(point, data);
            } else {
                if (!bottomLeftTree_) {
                    bottomLeftTree_ = std::make_unique<Quadtree>(
                        Point(topLeft_.getX(), midY), Point(midX, bottomRight_.getY()));
                }
                bottomLeftTree_->insertImpl(point, data);
            }
        } else {
            if (point.getY() <= midY) {
                if (!topRightTree_) {
                    topRightTree_ = std::make_unique<Quadtree>(
                        Point(midX, topLeft_.getY()), Point(bottomRight_.getX(), midY));
                }
                topRightTree_->insertImpl(point, data);
            } else {
                if (!bottomRightTree_) {
                    bottomRightTree_ = std::make_unique<Quadtree>(
                        Point(midX, midY), bottomRight_);
                }
                bottomRightTree_->insertImpl(point, data);
            }
        }
    }

    void splitAndInsert(const Point& existingPoint, const T& existingData) {
        // Create all four quadrants
        int midX = (topLeft_.getX() + bottomRight_.getX()) / 2;
        int midY = (topLeft_.getY() + bottomRight_.getY()) / 2;
        topLeftTree_ = std::make_unique<Quadtree>(topLeft_, Point(midX, midY));
        topRightTree_ = std::make_unique<Quadtree>(
            Point(midX, topLeft_.getY()), Point(bottomRight_.getX(), midY));
        bottomLeftTree_ = std::make_unique<Quadtree>(
            Point(topLeft_.getX(), midY), Point(midX, bottomRight_.getY()));
        bottomRightTree_ = std::make_unique<Quadtree>(
            Point(midX, midY), bottomRight_);

        insertImpl(existingPoint, existingData);
    }

    const T* searchImpl(const Point& point) const {
        if (!topLeftTree_ && hasPoint_ && point_.getX() == point.getX() && point_.getY() == point.getY()) {
            return data_.get();
        }

        int midX = (topLeft_.getX() + bottomRight_.getX()) / 2;
        int midY = (topLeft_.getY() + bottomRight_.getY()) / 2;

        if (point.getX() <= midX) {
            if (point.getY() <= midY) {
                return topLeftTree_ ? topLeftTree_->searchImpl(point) : nullptr;
            }
            return bottomLeftTree_ ? bottomLeftTree_->searchImpl(point) : nullptr;
        }
        if (point.getY() <= midY) {
            return topRightTree_ ? topRightTree_->searchImpl(point) : nullptr;
        }
        return bottomRightTree_ ? bottomRightTree_->searchImpl(point) : nullptr;
    }
};

#endif // QUADTREE_H